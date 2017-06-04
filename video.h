#ifndef VIDEO_H
#define VIDEO_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <iostream>
using namespace cv;

class video : public QThread
{   Q_OBJECT
private:
    bool stop, initialized;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame, binaryImage;
    int frameRate, count, c1;
    VideoCapture capture;
    QImage img;
    Ptr< BackgroundSubtractor> pMOG;
signals:
    void processedImage(const QImage &image);
public slots:
    void sliderValue(int i);
protected:
    void run();
public:
    video(QObject *parent=0);
    ~video();
    int minArea;
    bool loadVideo();
    void Play();
    void Stop();
    bool isStopped() const;
    void motionDetection(Mat lastFrame);
    void saveVideo(VideoWriter* oVideoWriter, Mat *frame );
};

#endif // VIDEO_H
