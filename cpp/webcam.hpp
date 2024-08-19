#ifndef WEBCAM_HPP
#define WEBCAM_HPP

#include <string>
#include <opencv2/opencv.hpp>

class Webcam {
public:
    // Constructor
    Webcam(int device_id = 0);

    // Destructor
    ~Webcam();

    // Opens the webcam device
    // Returns true if successful, false otherwise
    bool open();

    // Closes the webcam device
    void close();

    // Returns true if the webcam is currently open, false otherwise
    bool isOpened() const;

    // Captures a screenshot/frame from the webcam
    // Returns a cv::Mat containing the frame data
    cv::Mat captureFrame();

    // Starts video recording
    // Parameters include the output file name and video format
    // Returns true if successful, false otherwise
    bool startRecording(const std::string& filename, int fourcc = cv::VideoWriter::fourcc('X', '2', '6', '4'));

    // Stops video recording
    void stopRecording();

    // Returns true if video recording is currently active, false otherwise
    bool isRecording() const;

    // Gets available device info of the webcam
    // Returns a string describing the device
    std::string getDeviceInfo() const;

private:
    int device_id;           // The ID of the webcam device
    cv::VideoCapture cap;    // OpenCV object to interact with the webcam
    cv::VideoWriter writer;  // OpenCV object to handle video writing
    bool recording;          // Indicates if video recording is active
};

#endif // WEBCAM_HPP
