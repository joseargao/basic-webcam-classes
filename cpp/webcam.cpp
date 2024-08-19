#include "webcam.hpp"

// Constructor
Webcam::Webcam(int device_id) : device_id(device_id), recording(false) {}

// Destructor
Webcam::~Webcam() {
    close();
}

bool Webcam::open() {
    return cap.open(device_id);
}

void Webcam::close() {
    if (recording) {
        stopRecording();
    }

    if (cap.isOpened()) {
        cap.release();
    }
}

bool Webcam::isOpened() const {
    return cap.isOpened();
}

cv::Mat Webcam::captureFrame() {
    if (!cap.isOpened()) {
        throw std::runtime_error("Webcam is not open.");
    }

    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) {
        throw std::runtime_error("Failed to capture frame.");
    }

    // If recording, write the frame to the video file
    if (recording) {
        writer.write(frame);
    }

    return frame;
}

bool Webcam::startRecording(const std::string& filename, int fourcc) {
    if (cap.isOpened()) {
        int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
        int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

        writer.open(filename, fourcc, 30.0, cv::Size(width, height), true);
        if (!writer.isOpened()) {
            return false;
        }
        recording = true;
        return true;
    }
    return false;
}

void Webcam::stopRecording() {
    if (recording) {
        writer.release();
        recording = false;
    }
}

bool Webcam::isRecording() const {
    return recording;
}

std::string Webcam::getDeviceInfo() const {
    // Expand this with additional info if desired
    return "Webcam ID: " + std::to_string(device_id);
}
