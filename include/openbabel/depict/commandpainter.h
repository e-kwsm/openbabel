/**********************************************************************
commandpainter.h  - Render as depiction commands

Copyright (C) 2012 by Noel O'Boyle

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
#ifndef OB_COMMANDPAINTER_H
#define OB_COMMANDPAINTER_H

#include <openbabel/depict/painter.h>

namespace OpenBabel
{
  class CommandPainter : public OBPainter
  {
    public:
      CommandPainter(std::ostream& ofs);
      ~CommandPainter() override;
      //! @name OBPainter methods
      //@{
      void NewCanvas(double width, double height) override;
      bool IsGood() const override;
      void SetFontFamily(const std::string &fontFamily) override {} // FIXME
      void SetFontSize(int pointSize) override;
      void SetFillColor(const OBColor &color) override;
      void SetFillRadial(const OBColor &start, const OBColor &end) override;
      void SetPenColor(const OBColor &color) override;
      void SetPenWidth(double width) override;
      double GetPenWidth() override;
      void DrawLine(double x1, double y1, double x2, double y2, const std::vector<double> & dashes=std::vector<double>()) override;
      void DrawPolygon(const std::vector<std::pair<double,double> > &points) override;
      void DrawCircle(double x, double y, double r) override;
      void DrawBall(double x, double y, double r, double opacity = 1.0) override;
      void DrawText(double x, double y, const std::string &text) override;
      OBFontMetrics GetFontMetrics(const std::string &text) override;
      //@}

      //! @name CommandPainter specific
      //@{
      //@}

    private:
      std::ostream& m_ofs;
      std::streamsize m_oldprec;
      double m_pen_width;
  };

}

#endif
