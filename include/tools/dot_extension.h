/*
  Implementation of utility functions which make a system call
  to graphiz in order to generate image representations of graphs
  using their dot-representation.
  
  @author Christian González León
 */

#ifndef DOT_EXTENCION_H
#define DOT_EXTENCION_H

#include <string>
#include <fstream>
#include <cstdlib>

struct dot_extension {
  static std::string dotPath = "dot"; // asuming that is in the system path  

  inline static bool dotRepr2PNG(const std::string& dot_repr,
      const std::string& filename, const std::string& folder = "") {
    std::ofstream ofs("graph.gv");
    if (ofs.fail()) {
      ofs.close();
      return false;
    }
    ofs << dot_repr;
    ofs.close();
    system((dotPath + " -Tpng graph.gv -o " + filename + ".png").c_str());
    if (!folder.empty()) {
      system(std::string("move " + filename + ".png " + folder).c_str());
    }
    return true;
  }

  inline static bool dotRepr2JPEG(const std::string& dot_repr,
      const std::string& filename, const std::string& folder = "") {
    std::ofstream ofs("graph.gv");
    if (ofs.fail()) {
      ofs.close();
      return false;
    }
    ofs << dot_repr;
    ofs.close();
    system((dotPath + " -Tjpeg graph.gv -o " + filename + ".jpg").c_str());
    if (!folder.empty()) {
      system(std::string("move " + filename + ".png " + folder).c_str());
    }
    return true;
  }  
  
  
}

#endif // DOT_EXTENCION_H
