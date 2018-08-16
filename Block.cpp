#include "Block.h"

Block::Block(std::vector<std::vector<unsigned int>>* matrix)
{
    Matrix = matrix;
    mBlock.insert(mBlock.begin(),5,std::vector<bool>(5,0));
    Color = new GLUI::Glui_Color(GLUI::Green);
}

Block::~Block()
{
    delete Color;
}

bool Block::Next()
{
    if(!Matrix)
        return false;
    Y++;
    bool b = true;
    for(int i = -2; i < 3 && b; i++)    
    {
        for(int j = -2; j < 3 && b; j++)
        {
            if(!mBlock[i+2][j+2])
                continue;
            if(Y + i >= (int)Matrix->size())
            {
                b = false;
                break;
            }
            if(Y + i >= 0)
                b = (*Matrix)[Y+i][X+j] == 0;
            else b = true;
        }
    }
    Dead = !b;
    if(!b)
    {
        Y--;
        Save();
    }
    return b;
}

void Block::Left()
{
    if(Dead)
        return;
    X--;
    bool b = true;
    for(int i = -2; i < 3 && b; i++)    
    {
        for(int j = -2; j < 3 && b; j++)
        {
            if(!mBlock[i+2][j+2])
                continue;
            if(X + j < 0 || X + j >= (*Matrix)[0].size())
            {
                b = false;
                break;
            }
            if(Y + i < 0)
                continue;
            b = (*Matrix)[Y+i][X+j] == 0;
        }
    }
    if(!b)
        X++;
}

void Block::Right()
{
    if(Dead)
        return;
    X++;
    bool b = true;
    for(int i = -2; i < 3 && b; i++)    
    {
        for(int j = -2; j < 3 && b; j++)
        {
            if(!mBlock[i+2][j+2])
                continue;
            if(X + j < 0 || X + j >= (*Matrix)[0].size())
            {
                b = false;
                break;
            }
            if(Y + i < 0)
                continue;
            b = (*Matrix)[Y+i][X+j] == 0;
        }
    }
    if(!b)
        X--;
}

void Block::Rotate()
{
    if(Dead)
        return;
    //R_Full,R_semi,R_none
    switch (rType)
    {
        case R_Full:
            Rotate90();
            break;
        case R_semi:
            if(rutateIndex)
                Rotate90();
            else Rotate270();
            rutateIndex = !rutateIndex;
        default:
            break;
    }
}

void Block::setBlock(std::string str)
{
    rType = (RotateType)(str[0] - '0');
    Y = (str[1] - '0');
    if(Matrix)
        X = (*Matrix)[0].size()/2;
    for(int i = 0; i < 25; i++)
    {
        mBlock[i/5][i%5] = str[i + 2] == '+';
    } 
}

void Block::Print(float x,float y,float w,float h)
{
    if(!Matrix)
        return;
    for(int i = -2; i < 3; i++)
    {
        if(Y + i < 0 || Y + i >= Matrix->size())
            continue;
        for(int j = -2; j < 3; j++)
        {
            if(X + j < 0 || X + j >= (*Matrix)[0].size())
                continue;
            if(mBlock[i+2][j+2])
                GLUI::Gl_Print_Rectangle(x+(X + j)*w,y+(Matrix->size()- Y - i - 1)*h,w,h,*Color,GLUI::White,0,true,1);
        }        
    }   
}

void Block::Save()
{
    for(int i = -2; i < 3; i++)
    {
        if(Y + i < 0 || Y + i >= Matrix->size())
            continue;
        for(int j = -2; j < 3; j++)
        {
            if(X + j < 0 || X + j >= (*Matrix)[0].size())
                continue;
            if(mBlock[i+2][j+2])
                (*Matrix)[Y + i][X +j] = Color->getUInt();
        }        
    }   
}

void Block::Rotate90(bool Adjustment)
{
    bool tmp;
    int n = 5;
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n - 1 - i; j++)
        {
            tmp = mBlock[i][j];
            mBlock[i][j] = mBlock[n - j - 1][i];
            mBlock[n - j - 1][i] = mBlock[n - i - 1][n - j - 1];
            mBlock[n - i - 1][n - j - 1] = mBlock[j][n - i - 1];
            mBlock[j][n - i - 1] = tmp;
        }
    }
    if(Adjustment)
        if(!PositionAdjustment())
            Rotate270(false);
}

void Block::Rotate270(bool Adjustment)
{
    bool tmp;
    int n = 5;
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n - 1 - i; j++)
        {
            tmp = mBlock[i][j];
            mBlock[i][j] = mBlock[j][n - 1 - i];
            mBlock[j][n - 1 - i] = mBlock[n - 1 - i][n - 1 - j];
            mBlock[n - 1 - i][n - 1 - j] = mBlock[n - 1 - j][i];
            mBlock[n - 1 - j][i] = tmp;
        }
    }
    if(Adjustment)
        if(!PositionAdjustment())
            Rotate90(false);
}

bool Block::PositionAdjustment(BYTE deep)
{
    if(deep == 0)
        return 0;
    bool b = true;
    for(int i = -2; i < 3 && b; i++)    
    {
        for(int j = -2; j < 3 && b; j++)
        {
            if(!mBlock[i+2][j+2])
                continue;
            if(X + j < 0)
            {
                X++;
                b = PositionAdjustment(deep-1);
                if(!b)
                    X--;
                break;    
            } 
            if (X + j >= (*Matrix)[0].size())
            {
                X--;
                b = PositionAdjustment(deep-1);
                if(!b)
                    X++;
                break;
            }
            //if(Y + i > 0 && Y + i < Matrix->size())   <------the bug was here
            if(Y + i >= 0 && Y + i < Matrix->size())
                b = (*Matrix)[Y+i][X+j] == 0;
            else b = false;
            if(Y + i < 0)
                b = true;
        }
    }
    return b;
}

void Block::setBlockColor(const GLUI::Glui_Color& color)
{
    if(Color)
        delete Color;
    Color  = new GLUI::Glui_Color(color);
}