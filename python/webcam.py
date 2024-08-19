#!/usr/bin/env python3
import cv2

class Webcam:
    def __init__(self, device_id):
        self.device_id = device_id
        self.cap = None
        self.writer = None
        self.recording = False

    def open(self):
        self.cap = cv2.VideoCapture(self.device_id)
        return self.cap.isOpened()

    def close(self):
        if self.cap and self.cap.isOpened():
            self.cap.release()
        if self.recording:
            self.stop_recording()

    def is_opened(self):
        return self.cap.isOpened() if self.cap else False

    def capture_frame(self):
        if not self.is_opened():
            return None
        ret, frame = self.cap.read()
        if ret:
            return frame
        return None

    def start_recording(self, filename):
        if self.is_opened():
            fourcc = cv2.VideoWriter_fourcc(*'MJPG')
            width = int(self.cap.get(cv2.CAP_PROP_FRAME_WIDTH))
            height = int(self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
            fps = 30
            self.writer = cv2.VideoWriter(filename, fourcc, fps, (width, height))
            self.recording = True

    def stop_recording(self):
        if self.recording and self.writer:
            self.writer.release()
            self.recording = False

    def get_device_info(self):
        if not self.is_opened():
            return "Device not opened"
        width = int(self.cap.get(cv2.CAP_PROP_FRAME_WIDTH))
        height = int(self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
        fps = self.cap.get(cv2.CAP_PROP_FPS)
        info = f"Width: {width}, Height: {height}, FPS: {fps}"
        return info
