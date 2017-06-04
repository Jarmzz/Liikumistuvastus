#include "video.h"
#include <QDateTime>



video::video(QObject *parent)
 : QThread(parent)
{
    stop = true;
}

bool video::loadVideo(){
    if(!capture.isOpened())
    {
        capture.open(0);
        frameRate = capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;
}
void video::Play(){
    if(!isRunning()){
        if(isStopped()){
            stop = false;
        }
        start(LowPriority);
    }
}
void video::run()
{
    initialized = true;
    Mat fgMaskMOG1, mainFrame, RGBframe;
    pMOG =  createBackgroundSubtractorMOG2(100,64,false);
    capture.read(frame);
    c1 = 30;
    int width = frame.size().width;
    int height = frame.size().height;
    Size frameSize(static_cast<int>(width), static_cast<int>(height));
    VideoWriter oVideoWriter ("C:\\Users\\rsasalt\\Documents\\xd\\SUPERSEKTRETNSAFILE.avi", CV_FOURCC('W','M','V','2'), 24, frameSize);
    while(!stop){
        if (!capture.read(frame))
        {
            stop = true;
        }
        mainFrame = frame;
        motionDetection(frame);

        if (frame.channels()== 3){
            cvtColor(frame, RGBframe, CV_BGR2RGB);
            img = QImage((const unsigned char*)(RGBframe.data),
                              RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);
        }
        else
        {
            img = QImage((const unsigned char*)(frame.data),
                              frame.cols,frame.rows,QImage::Format_Indexed8);
        }
        if(count >= (15))
        {
            //cvtColor(frame, mainFrame, CV_BGR2RGB);
            oVideoWriter.write(this->frame);
            if(initialized == true)
            {
                system("python saadasms.py");
                initialized = false;
            }
        }
        if(!stop){
            emit processedImage(img);
        }
    }
    oVideoWriter.release();
}
video::~video()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}
void video::Stop()
{
    stop = true;
}
bool video::isStopped() const{
    return this->stop;
}
void video::sliderValue(int i)
{
    minArea = i;
}

void video::motionDetection(Mat lastFrame){
    Mat fgMaskMOG1;
    Mat ContourImg;
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(7, 7), Point(1, 1));
    Mat element1 = getStructuringElement(MORPH_RECT, Size(21, 21), Point(15,15) );
    blur(lastFrame, fgMaskMOG1, Size(10,10));
    pMOG->apply(fgMaskMOG1, fgMaskMOG1,-0.5);
    dilate(fgMaskMOG1,fgMaskMOG1,element);
    morphologyEx(fgMaskMOG1, binaryImage, CV_MOP_CLOSE, element1);
    threshold(binaryImage,binaryImage,64,255,CV_THRESH_BINARY);
    dilate(binaryImage,binaryImage, element);
    ContourImg = binaryImage.clone();
    std::vector< std::vector< Point> > contours;
    findContours(ContourImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    std::vector< std::vector< Point> >::iterator itc= contours.begin();
    if(contours.empty() || contourArea(*itc)<=1000){
                c1= c1-1;
                if(c1 == 0)
                {
                    count = 0;
                    c1=25;
                    initialized = true;
                }
            }
    while (itc!=contours.end()) {
        if(contourArea(*itc)>1000){
            count++;
            Rect mr= boundingRect(Mat(*itc));
            rectangle(frame, mr, Scalar(0,0,255));
            c1=30;

            }
        ++itc;
    }
}
void video::saveVideo(VideoWriter* oVideoWriter, Mat* frame ){
       if (!oVideoWriter->isOpened() )
       {
            return;
        }
        oVideoWriter->write(*frame);
            return;
}
