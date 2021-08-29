using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace GELightsSimulator
{
   class Bulb
   {
      int id = -1; // bulb address
      Color c = Color.Black; // colour of the bulb - default is black
      Pen BulbBorder = Pens.White; // the border of the bulb
      Brush BulbBackground = Brushes.Black; // the background of the bulb
      Rectangle big = Rectangle.Empty; // the rectangle including the border
      Rectangle small = Rectangle.Empty; // the rectangle excluding the border

      public Bulb(int Id, int x, int y)
      {
         // save the address
         id = Id;

         // work out the rectangles
         big = new Rectangle(x, y, 10, 10);
         small = new Rectangle(x+1, y+1, 8, 8);
      }

      public void Set(int r, int g, int b, int brightness)
      {
         // create the colour
         c = Color.FromArgb(brightness, r*16, g*16, b*16);
      }
      public void SetBrightness(int brightness)
      {
         // create the colour
         c = Color.FromArgb(brightness, c.R, c.G, c.B);
      }

      public void Draw(Graphics G)
      {
         // draw the bulb background
         G.FillEllipse(BulbBackground, big);

         // draw the outline
         G.DrawEllipse(BulbBorder, big);

         // draw the bulb content
         G.FillEllipse(new SolidBrush(c), small);
      }

      public Rectangle GetRectangle()
      {
         // return the area to invalidate
         return small;
      }
   }
}
