using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Xml;
using System.Xml.XPath;
using System.Diagnostics;

namespace GELightsSimulator
{
   public partial class Form1 : Form
   {         
      Bulb[,] bulbs = new Bulb[8,50]; // our bulb

      // decode into a bit
      int getbit(int bit1, int bit2, int bit3)
      {
         // 011 --> 0
         if (bit1 == 0 && bit2 != 0 && bit3 != 0)
         {
            return 0;
         }
         // 001 --> 1
         else if (bit1 == 0 && bit2 == 0 && bit3 != 0)
         {
            return 1;
         }
         else
         {
            // not a valid bit pattern
            Debug.Fail("Invalid bit");
            return -1;
         }
      }

      // decode the message into its parameters
      public void DecodeBytes(byte[] b, ref int red, ref int green, ref int blue, ref int brightness, ref int address)
      {
         // check the preamble
         if ((b[0] & (byte)(128 + 64 + 32)) != 0)
         {
            Debug.Fail("Missing leading 000");
         }

         // check the start bit
         if ((b[0] & (byte)(16)) == 0)
         {
            Debug.Fail("Missing start bit");
         }

         // extract the address
         address = getbit(b[0] & (byte)(8), b[0] & (byte)(4), b[0] & (byte)(2)) * 32 +
                       getbit(b[0] & (byte)(1), b[1] & (byte)(128), b[1] & (byte)(64)) * 16 +
                       getbit(b[1] & (byte)(32), b[1] & (byte)(16), b[1] & (byte)(8)) * 8 +
                       getbit(b[1] & (byte)(4), b[1] & (byte)(2), b[1] & (byte)(1)) * 4 +
                       getbit(b[2] & (byte)(128), b[2] & (byte)(64), b[2] & (byte)(32)) * 2 +
                       getbit(b[2] & (byte)(16), b[2] & (byte)(8), b[2] & (byte)(4)) * 1;
         
         // extract the brightness
         brightness = getbit(b[2] & (byte)(2), b[2] & (byte)(1), b[3] & (byte)(128)) * 128 +
                          getbit(b[3] & (byte)(64), b[3] & (byte)(32), b[3] & (byte)(16)) * 64 +
                          getbit(b[3] & (byte)(8), b[3] & (byte)(4), b[3] & (byte)(2)) * 32 +
                          getbit(b[3] & (byte)(1), b[4] & (byte)(128), b[4] & (byte)(64)) * 16 +
                          getbit(b[4] & (byte)(32), b[4] & (byte)(16), b[4] & (byte)(8)) * 8 +
                          getbit(b[4] & (byte)(4), b[4] & (byte)(2), b[4] & (byte)(1)) * 4 +
                          getbit(b[5] & (byte)(128), b[5] & (byte)(64), b[5] & (byte)(32)) * 2 +
                          getbit(b[5] & (byte)(16), b[5] & (byte)(8), b[5] & (byte)(4)) * 1;
         
         // extract blue
         blue = getbit(b[5] & (byte)(2), b[5] & (byte)(1), b[6] & (byte)(128)) * 8 +
                    getbit(b[6] & (byte)(64), b[6] & (byte)(32), b[6] & (byte)(16)) * 4 +
                    getbit(b[6] & (byte)(8), b[6] & (byte)(4), b[6] & (byte)(2)) * 2 +
                    getbit(b[6] & (byte)(1), b[7] & (byte)(128), b[7] & (byte)(64)) * 1;
         
         // extract green
         green = getbit(b[7] & (byte)(32), b[7] & (byte)(16), b[7] & (byte)(8)) * 8 +
                     getbit(b[7] & (byte)(4), b[7] & (byte)(2), b[7] & (byte)(1)) * 4 +
                     getbit(b[8] & (byte)(128), b[8] & (byte)(64), b[8] & (byte)(32)) * 2 +
                     getbit(b[8] & (byte)(16), b[8] & (byte)(8), b[8] & (byte)(4)) * 1;
         
         // extract red
         red = getbit(b[8] & (byte)(2), b[8] & (byte)(1), b[9] & (byte)(128)) * 8 +
                   getbit(b[9] & (byte)(64), b[9] & (byte)(32), b[9] & (byte)(16)) * 4 +
                   getbit(b[9] & (byte)(8), b[9] & (byte)(4), b[9] & (byte)(2)) * 2 +
                   getbit(b[9] & (byte)(1), b[10] & (byte)(128), b[10] & (byte)(64)) * 1;
      }

      protected override void WndProc(ref Message m)
      {
         // if it is our notification
         if (m.Msg == 1024)
         {
            // buffer to hold the message
            byte[] b = new byte[11];
            string s = null;

            try
            {
               // get the clipboard data
               IDataObject iData = Clipboard.GetDataObject();
               if (iData.GetDataPresent(DataFormats.Text))
               {
                  s = (string)iData.GetData(DataFormats.Text);
               }

               // parse it into an array of bytes
               for (int i = 0; i < 11; i++)
               {
                  string hex = s.Substring(i * 3, 3);
                  b[i] = Byte.Parse(hex);
               }
            }
            catch (Exception ex)
            {
               // show an error
               MessageBox.Show(ex.Message);
            }

            // decode the message
            int red = 0;
            int green = 0;
            int blue = 0;
            int brightness = 0;
            int address = 0;
            DecodeBytes(b, ref red, ref green, ref blue, ref brightness, ref address);

            // process the message
            ProcessMessage(m.WParam.ToInt32(), address, red, green, blue, brightness);
         }
         else
         {
            // pass all other messages on
            base.WndProc(ref m);
         }
      } 

      public Form1()
      {
         InitializeComponent();

         // load the xml document that specifies the bulb screen locations
         XPathDocument doc;
         try
         {
            doc = new XPathDocument(File.Open("GELightsSimulator.xml", FileMode.Open));
         }
         catch
         {
            doc = null;
         }

         // if we loaded the document
         if (doc != null)
         {
            // create an xpath navigator
            XPathNavigator nav = doc.CreateNavigator();

            for (int j = 0; j < 8; j++)
            {
               try
               {
                  // for each bulb
                  for (int i = 0; i < 50; i++)
                  {
                     // extract the x position
                     XPathExpression exprX = nav.Compile("//number[. = '" + j.ToString().Trim() + "_" + i.ToString().Trim() + "']/parent::node()/x");
                     XPathNodeIterator iterX = nav.Select(exprX);
                     iterX.MoveNext();
                     int x = Int16.Parse(iterX.Current.Value);

                     // extract the y position
                     XPathExpression exprY = nav.Compile("//number[. = '" + j.ToString().Trim() + "_" + i.ToString().Trim() + "']/parent::node()/y");
                     XPathNodeIterator iterY = nav.Select(exprY);
                     iterY.MoveNext();
                     int y = Int16.Parse(iterY.Current.Value);

                     // create the bulb
                     bulbs[j, i] = new Bulb(i, x, y);
                  }
               }
               catch
               {
               }
            }
         }
         else
         {
            // create a default layout
            int x;
            for (int j = 0; j < 5; j++)
            {
               for (int i = 0; i < 10; i++)
               {
                  if (j == 1 || j == 3)
                  {
                     x = 30 + 9 * 14 - i * 14;
                  }
                  else
                  {
                     x = 30 + i * 14;
                  }

                  bulbs[0, j * 10 + i] = new Bulb(j * 10 + i, x, 30 + j * 14);
               }
            }
         }
      }

      public delegate void ProcessMessageDelegate(int address, int r, int g, int b, int brightness);
      public void ProcessMessage(int stringofbulbs, int address, int r, int g, int b, int brightness)
      {
         // if it is a broadcast message
         if (address == 63)
         {
            // for each bulb
            for (int i = 0; i < 50; i++)
            {
               // apply brightness only
               bulbs[stringofbulbs, i].SetBrightness(brightness);

               // tell it to repaint
               Invalidate(bulbs[stringofbulbs, i].GetRectangle());
            }
         }
         else
         {
            // set all the bulb details
            bulbs[stringofbulbs, address].Set(r, g, b, brightness);

            // tell it to repaint
            Invalidate(bulbs[stringofbulbs, address].GetRectangle());
         }
      }

      private void Form1_Paint(object sender, PaintEventArgs e)
      {
         // paint all the bulbs
         foreach (Bulb b in bulbs)
         {
            if (b != null)
            {
               b.Draw(e.Graphics);
            }
         }
      }
   }
}
