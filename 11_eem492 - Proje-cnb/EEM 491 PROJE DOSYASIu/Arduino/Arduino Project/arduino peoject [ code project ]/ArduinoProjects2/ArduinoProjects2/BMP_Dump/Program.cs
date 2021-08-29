using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Text;


namespace BMP_Dump
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("This program dumps a monochrome image to a text file.");
			Console.WriteLine("");
			Console.WriteLine("In order to use an image, it must be:");
			Console.WriteLine("  * A BMP file");
			Console.WriteLine("  * A Monochrome (only black and white),");
			Console.WriteLine("    but saved in a noncompressed format (16-bit or 24-bit file format)"); // 
			Console.WriteLine("  * Width divisible by 8");
			Console.WriteLine("");
			Console.WriteLine("");

			string strFilePath = args[0];
			int nExtensionPos = strFilePath.LastIndexOf('.');
			string strOutputFilePath = strFilePath.Substring(0, nExtensionPos) + ".txt";

			Image image = Image.FromFile(strFilePath);
			Bitmap bitmap = new Bitmap(image);


			TextWriter textWriter = new StreamWriter(strOutputFilePath);

				
			/**/
			WriteLine(textWriter, "Raw bits version");
			for(int y = 0; y < bitmap.Height; ++y)
			{
				for(int x = 0; x < bitmap.Width; ++x)
				{
					Color color = bitmap.GetPixel(x, y);
					if(color.B == 0 && color.G == 0 && color.R == 0)
					{
						Write(textWriter, "1,");
					}
					else if(color.B == 255 && color.G == 255 && color.R == 255)
					{
						Write(textWriter, "0,");
					}
					else
					{
						Write(textWriter, "?,");
					}
				}

				WriteLine(textWriter, "");
			}


			/**/
			WriteLine(textWriter, "");
			WriteLine(textWriter, "");
			WriteLine(textWriter, "RLE version");
			for(int y = 0; y < bitmap.Height; ++y)
			{
				Color lastColor = bitmap.GetPixel(0, y);
				if(lastColor.B == 0 && lastColor.G == 0 && lastColor.R == 0)
				{
					Write(textWriter, "1,");
				}
				else if(lastColor.B == 255 && lastColor.G == 255 && lastColor.R == 255)
				{
					Write(textWriter, "0,");
				}
				else
				{
					Write(textWriter, "?,");
				}

				int nCount = 1;
				for(int x = 1; x < bitmap.Width; ++x)
				{
					Color color = bitmap.GetPixel(x, y);
					if(color != lastColor)
					{
						Write(textWriter, String.Format("{0},", nCount));
						lastColor = color;
						nCount = 0;
					}

					nCount++;
				}

				WriteLine(textWriter, String.Format("{0},-1,", nCount));
			}
			WriteLine(textWriter, "-42");
			
			
			/**/
			// DrawBitmap version is bassed off the Python code found at:
			// http://registry.gimp.org/node/14964
			WriteLine(textWriter, "");
			WriteLine(textWriter, "");
			WriteLine(textWriter, "DrawBitmap() version");
		    WriteLine(textWriter, "#include <avr/pgmspace.h>");
		    WriteLine(textWriter, "");
			WriteLine(textWriter, "static uint8_t newBitmap[] PROGMEM = {");
			WriteLine(textWriter, String.Format("\t{0}, \\\\ Bitmap width", bitmap.Width));
			WriteLine(textWriter, String.Format("\t{0}, \\\\ Bitmap height", bitmap.Height));
			/*
			for y in range(0,height, 8):
				for x in range(0,width, 8):
					for xx in range(0,8):
						byte = 0
						for yy in range(0,8):
							(channels,pixel) = pdb.gimp_drawable_get_pixel(drawable,x + xx, y + yy)
							byte = byte | ( pixel[0] << yy )
						fileOut.write("0x%02X, " % byte)
					gimp.progress_update(float(x+y*width)/(width*height))
					fileOut.write( "\n" )
			*/
			for(int y = 0; y < bitmap.Height; y += 8)
			{
				for(int x = 0; x < bitmap.Width; x += 8)
				{
					Write(textWriter, "\t");
					for(int xx = 0; xx < 8; xx++)
					{
						int theByte = 0;
						for(int yy = 0; yy < 8; yy++)
						{
							Color lastColor = bitmap.GetPixel(x + xx, y + yy);
							byte pixel = 0;
							if(lastColor.B == 0 && lastColor.G == 0 && lastColor.R == 0)
							{
								pixel = 1;
							}

							theByte = theByte | (pixel << yy);
						}

						Write(textWriter, String.Format("0x{0}, ", theByte.ToString("X2")));
					}

					WriteLine(textWriter, "");
				}
			}

			WriteLine(textWriter, "};");

	
			textWriter.Close();
			System.Console.WriteLine("All finished.  Press any key to continue.");
			System.Console.Read();
		}

		static void Write(TextWriter textWriter, string str)
		{
			Console.Write(str);
			textWriter.Write(str);
		}

		static void WriteLine(TextWriter textWriter, string str)
		{
			Console.WriteLine(str);
			textWriter.WriteLine(str);
		}
	}
}
