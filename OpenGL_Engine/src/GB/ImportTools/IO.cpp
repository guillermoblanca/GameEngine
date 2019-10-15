#include "gbpch.h"
#include "IO.h"
#include <Commdlg.h>

bool GB::IO::GetPathDialogBox(std::string & OutPath)
{
  char filename[MAX_PATH];

  OPENFILENAMEA ofn;
  ZeroMemory(&filename, sizeof(filename));
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
  ofn.lpstrFilter = "Textures\0.png\0 GBEngine Files\0*.gb\0Text Files\0*.txt\0Any File\0*.*\0";
  ofn.lpstrFile = filename;
  ofn.nMaxFile = MAX_PATH;
  ofn.lpstrTitle = "GB Select File";
  //ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

  if (GetOpenFileNameA(&ofn))
  {
    OutPath = filename;
    return true;
  }
  return false;
}
