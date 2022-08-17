/**********************************************************************
svgpainter.h - Rendering in SVG

Copyright (C) 2009 by Chris Morley

This file is part of the Open Babel project.
For more information, see <http://openbabel.org/>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
***********************************************************************/
#ifndef OB_SVGPAINTER_H
#define OB_SVGPAINTER_H

#include <openbabel/babelconfig.h>
#include <iostream>
#include <set>
#include <openbabel/depict/painter.h>

namespace OpenBabel
{
  typedef std::pair<OBColor,OBColor> ColorGradient;

  class OBDEPICT SVGPainter : public OBPainter
  {
    public:
      SVGPainter();
      SVGPainter(std::ostream& ofs, std::set<ColorGradient> *gradients, bool withViewBox=false,
        double width=0.0, double height=0.0);
      ~SVGPainter() override;
      //! @name OBPainter methods
      //@{
      void NewCanvas(double width, double height) override;
      void EndCanvas();
      bool IsGood() const override;
      void SetFontFamily(const std::string &fontFamily) override;
      void SetFontSize(int pointSize) override;
      void SetFillColor(const OBColor &color) override;
      void SetFillRadial(const OBColor &start, const OBColor &end) override;
      void SetPenColor(const OBColor &color) override;
      void SetPenWidth(double width) override;
      double GetPenWidth() override;
      void DrawLine(double x1, double y1, double x2, double y2, const std::vector<double>& dashes=std::vector<double>()) override;
      void DrawPolygon(const std::vector<std::pair<double,double> > &points) override;
      void DrawCircle(double x, double y, double r) override;
      void DrawBall(double x, double y, double r, double opacity = 1.0) override;
      void DrawText(double x, double y, const std::string &text) override;
      OBFontMetrics GetFontMetrics(const std::string &text) override;
      void WriteDefs();
      //@}

      //! @name CairoPainter specific
      //@{
      void WriteImage(const std::string &filename);
      //@}
    private:
      std::string RGBcode(OBColor color);
      std::string MakeRGB(OBColor color);

    private:
      std::ostream& m_ofs;
      bool m_withViewBox;
      double m_width, m_height;
      OBColor m_Pencolor;
      OBColor m_OrigBondcolor;
      OBColor m_Fillcolor;
      ColorGradient m_Gradientcolor;
      std::set<ColorGradient> *m_Gradients;
      bool m_isFillcolor;
      double m_PenWidth;
      int m_fontPointSize;
      std::string m_fontFamily;
  };

}

#endif

//! \file svgpainter.h
//! \brief Generate 2D depictions in the SVG vector graphics format.
