#include "pixy2/Camera.h"

using namespace lima;
using namespace lima::pixy2;

//---------------------------
//- OpenCV methods
//---------------------------
cv::Mat Camera::toMat(uint8_t * img)
{
  return cv::Mat(cv::Size(PIXY2_RAW_FRAME_WIDTH, PIXY2_RAW_FRAME_HEIGHT),CV_8UC1, img);
}

uint8_t * Camera::touint8(cv::Mat img)
{
  if (img.isContinuous())
    return img.ptr<uint8_t>(0);
  return nullptr;
}
void MyLine(cv::Mat img, cv::Point start, cv::Point end )
{
  int thickness = 1;
  int lineType = cv::LINE_8;
  cv::line( img,
    start,
    end,
    cv::Scalar( 255 ),
    thickness);
}
uint8_t * Camera::draw(uint8_t * img)
{
    uint8_t * tmp = img;
    switch (prog)
    {
      case 1:
        cv::Mat input_img = toMat(tmp);
        for(int i = 0; i < begin_line_point.size(); i++)
          MyLine(input_img, begin_line_point[i]*316/100, end_line_point[i]*208/100);
        tmp=touint8(input_img)
        break;
      case 2:
        cv::Mat input_img = toMat(tmp);
        for(int i = 0; i < begin_square_point.size(); i++)
          cv::rectangle(input_img, begin_square_point[i], end_square_point[i], cv::Scalar(255), 2);//Drawing the rectangle//
        tmp=touint8(input_img)
        break;
      default:
        break;
    }
    return tmp;
}

void  Camera::get_square_features()
{
  pixy.changeProg("color_connected_components");
  get_blocks();
}

//---------------------------
//- Internal
//---------------------------
void  Camera::get_blocks()
{
  int  Block_Index;

  pixy.ccc.getBlocks();

    printf ("pixy.ccc.numBlocks %d block(s)\n", pixy.ccc.numBlocks);
  if (pixy.ccc.numBlocks)
  {
    for (Block_Index = 0; Block_Index < pixy.ccc.numBlocks; ++Block_Index)
    {
      begin_square_point.push_back(cv::Point(pixy.ccc.blocks[Block_Index].m_x,pixy.ccc.blocks[Block_Index].m_y));
      end_square_point.push_back(cv::Point(pixy.ccc.blocks[Block_Index].m_width,pixy.ccc.blocks[Block_Index].m_height));
    }
  }
}

void  Camera::get_line_features()
{
  begin_line_point.clear();
  end_line_point.clear();
  int  Element_Index;

  // Query Pixy for line features //
  pixy.line.getAllFeatures();

  // Were vectors detected? //
  if (pixy.line.numVectors)
  {
    // Blocks detected - print them! //


    for (Element_Index = 0; Element_Index < pixy.line.numVectors; ++Element_Index)
    {
      printf ("  Vector %d: ", Element_Index + 1);
      pixy.line.vectors[Element_Index].print();
      begin_line_point.push_back(cv::Point(pixy.line.vectors[Element_Index].m_x0 ,pixy.line.vectors[Element_Index].m_y0));
      end_line_point.push_back(cv::Point(pixy.line.vectors[Element_Index].m_x1, pixy.line.vectors[Element_Index].m_y1));
    }
  }
}
void Camera::demosaic(uint16_t width, uint16_t height, const uint8_t *bayerImage, uint32_t *image)
{
  uint32_t x, y, xx, yy, r, g, b;
  uint8_t *pixel0, *pixel;
  
  for (y=0; y<height; y++)
  {
    yy = y;
    if (yy==0)
      yy++;
    else if (yy==height-1)
      yy--;
    pixel0 = (uint8_t *)bayerImage + yy*width;
    for (x=0; x<width; x++, image++)
    {
      xx = x;
      if (xx==0)
	xx++;
      else if (xx==width-1)
	xx--;
      pixel = pixel0 + xx;
      if (yy&1)
      {
        if (xx&1)
        {
          r = *pixel;
          g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
          b = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
        }
        else
        {
          r = (*(pixel-1)+*(pixel+1))>>1;
          g = *pixel;
          b = (*(pixel-width)+*(pixel+width))>>1;
        }
      }
      else
      {
        if (xx&1)
        {
          r = (*(pixel-width)+*(pixel+width))>>1;
          g = *pixel;
          b = (*(pixel-1)+*(pixel+1))>>1;
        }
        else
        {
          r = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
          g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
          b = *pixel;
        }
      }
      *image = (b<<16) | (g<<8) | r; 
    }
  }
}