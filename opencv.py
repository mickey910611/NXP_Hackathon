import cv2
import numpy as np
import pyautogui
from ultralytics import YOLO
from datetime import datetime
import time
import socket

time.sleep(3)
server_ip = '192.168.1.1'  # 替換為您的伺服器 IP
server_port = 8080

#創建 TCP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 連接到伺服器
client_socket.connect((server_ip, server_port))
# 初始化 YOLOv8 模型
model = YOLO("yolov8m.pt")

# 設定螢幕解析度
screen_width, screen_height = pyautogui.size()

frame_count = 0
detection_interval = 1  # 每幾幀進行一次檢測

# 定義感興趣區域 (ROI)
roi_start = (0, 100)  # 左上角
roi_end = (300, 400)    # 右下角

# 定義車輛類別 ID
vehicle_class_ids = {"汽車":2, "機車":3, "公車":5, "卡車": 7}

# 設定燈號時相
current=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
start=current

phase={"Green":24,"Yellow":3,"Red":53}
i=0
light=list(phase.keys())[i%3]
light_c=[(0, 255, 0),(0,255,255),(0,0,255)]
x=phase[light]

change=False
cancel=False

# 平均車數列表
veh={}
change_time=[]

while True:
    # 擷取螢幕畫面
    screenshot = pyautogui.screenshot()
    
    # 將 screenshot 轉為 NumPy array 格式
    frame = np.array(screenshot)
    
    # 縮放影像
    frame = cv2.resize(frame, (640, 480))

    # 繪製感興趣區域 (ROI)
    cv2.rectangle(frame, roi_start, roi_end, (255, 0, 0), 2)  # 用藍色框出 ROI 區域

    if x==0:
        now_light=(i-1)%3
    else:
        now_light=i%3
    
    cv2.putText(frame, f"{light}: {x}", (450, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, light_c[now_light], 2)
    #cv2.putText(frame, f"{now_light}: {x}", (450, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, light_c[now_light], 2)

    # 顯示現在時相
    current_time=datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    if current_time!=current:        
        current=current_time

        #print(now_light,x,int(change),int(cancel))
        mes = str(now_light) + ' ' + str(x) + ' ' + str(int(change)) + ' ' + str(int(cancel))
        client_socket.sendall(mes.encode('utf-8'))

        #print(mes)
        if light==list(phase.keys())[i%3]:
            x-=1
        else:
            light=list(phase.keys())[i%3]
            x=phase[light]

        if x==0:
            i+=1
            change=False
            cancel=False
            veh.clear()     
            change_time.clear()  

        # 處理車數        
        if len(veh)>=5:
            avg=0
            for sec in veh:
                if len(veh[sec]) == 0:
                    avg+=0
                else:
                    avg+=np.mean(veh[sec])
            (k := next(iter(veh)), veh.pop(k))

            if avg/5<2.5 and x>5:
                change=True

    frame_count += 1

    # 預備提早調時相
    if change and not cancel:
        if x not in change_time:
            change_time.append(x)
        cv2.putText(frame, f"Few cars last 5s.", (250, 60), cv2.FONT_HERSHEY_SIMPLEX, 1, light_c[(i-1)%3], 2)
        cv2.putText(frame, f"Change? Press c to cancel", (170, 90), cv2.FONT_HERSHEY_SIMPLEX, 1, light_c[(i-1)%3], 2)
        if cv2.waitKey(1) & 0xFF == ord('c'):
            cancel=True

    if change and len(change_time)>5 and cancel==False:
        check_change=0
        if len(list(veh.values())[-1])!=0:
            check_change=np.mean(list(veh.values())[-1])

        #print(len(change_time))
        if check_change<3:
            x=0
            i+=1
            change_time.clear()
            veh.clear()
        
        change=False

    # 車輛辨識
    if frame_count % detection_interval == 0:
        # 進行物體檢測
        results = model(frame, verbose=False)
    
        detected_objects = []
    
        # 迭代檢測結果
        for result in results:
            # 取得邊界框和類別 ID
            boxes = result.boxes
            for box in boxes:
                x1, y1, x2, y2 = box.xyxy[0].tolist()  # 邊界框座標 (x1, y1, x2, y2)
                conf = box.conf[0].item()  # 取得信心值
                class_id = int(box.cls[0].item())  # 取得類別 ID
    
                # 邊界框的中心點
                center_x = int((x1 + x2) / 2)
                center_y = int((y1 + y2) / 2)
    
                # 檢查邊界框的中心點是否在 ROI 範圍內
                if roi_start[0] < center_x < roi_end[0] and roi_start[1] < center_y < roi_end[1] and class_id in vehicle_class_ids.values():
                    # 繪製邊界框
                    color = (0, 255, 0)  # 綠色框
                    label = f"ID: {class_id} Conf: {conf:.2f}"
    
                    # 繪製邊界框
                    cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), color, 2)
                    
                    # 在邊界框上繪製標籤
                    cv2.putText(frame, label, (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)
    
                    # 儲存符合範圍的物體信息
                    detected_objects.append((class_id, conf))
    
            adjust_sec=phase[light]-6
            # 在綠燈秒數接近一半前5秒開始儲存車數
            if light=="Green" and x<adjust_sec+5:
                if x not in veh:
                    veh[x]=[]
            
            # 僅顯示方框內的檢測結果
            if detected_objects:
                detection_count = len(detected_objects)
                detection_info = '；'.join([f"信心值：{conf:.2f}，車種：{[k for k,v in vehicle_class_ids.items() if v==class_id][0]}" for class_id, conf in detected_objects])
                print(f"\n{light}: {x}",end=" ")

                now = datetime.now()
                formatted_time = now.strftime("%Y-%m-%d %H:%M:%S")
                print(f"{formatted_time} 共偵測到{detection_count}台車：{detection_info}")

                if light=="Green" and x<adjust_sec+5:
                    veh[x].append(detection_count)
    
    # 顯示帶有檢測結果的畫面
    cv2.imshow('Vehicle Detection with ROI', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        client_socket.close()
        break

# 釋放影片資源和關閉視窗
cv2.destroyAllWindows()