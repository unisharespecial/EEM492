using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;

namespace GELightsCompiler
{

   public partial class Form1 : Form
   {
      Dictionary<int, Command> commands = new Dictionary<int, Command>(); // these are the commands the compiler recognises
      Dictionary<string, int> decodetable = new Dictionary<string, int>(); // these are the keywords the compiler recognises
      Dictionary<string, string> defines = new Dictionary<string, string>(); // these are the define variables
      Dictionary<string, int> tags = new Dictionary<string, int>(); // these are loop tags and the distance from them we currently are
      Dictionary<string, Int16> vars = new Dictionary<string, Int16>(); // these are the variables we have already defined
      Int16 __var = -16100; // this is the number to use for the next variable name encountered

      // Increment the distance back to all tags we have seen so far
      void IncrementTags()
      {
         // for each tag
         foreach (string s in tags.Keys.ToArray<string>())
         {
            // incrmement the jump distance
            tags[s] = tags[s] + 1;
         }
      }

      // comile a list of files
      void CompileFiles(string[] files)
      {
         // generate a name for the .h file using the first file name
         string h = Path.GetDirectoryName(files[0]) + "\\" + Path.GetFileNameWithoutExtension(files[0]) + ".h"; // the CPP header output file

	 // delete any previously generated output file
         try
         {
            // delete any existing file
            if (File.Exists(h))
            {
               File.Delete(h);
            }
         }
         catch (Exception ex)
         {
            MessageBox.Show("Error deleting file " + h + " " + ex.Message);
            throw ex;
         }

         // open the header file
         StreamWriter hw;
         try{
            hw = new StreamWriter(File.Create(h));
         }
         catch (Exception ex)
         {
            MessageBox.Show("Error opening file " + h + " " + ex.Message);
            throw ex;
         }

         // write the header file preamble
         string macro = "_" + Path.GetFileNameWithoutExtension(files[0]).ToUpper() + "_H";
         hw.WriteLine("#ifndef " + macro);
         hw.WriteLine("#define " + macro);
         hw.WriteLine("");

         // for each file
         for (int i = 0; i < files.Count(); i++)
         {
            // compile it
            GELightsCompiler(files[i], i, hw);
         }

         // for any not present files write an empty definition
         for (int i = files.Count(); i < 6; i++)
         {
            hw.WriteLine("#ifdef PC");
            hw.WriteLine("short program" + i.ToString().Trim() + "[] = {-1};");
            hw.WriteLine("#else");
            hw.WriteLine("prog_int16_t program" + i.ToString().Trim() + "[] PROGMEM = {-1};");
            hw.WriteLine("#endif");
         }

         // write the header file postable
         hw.WriteLine("");
         hw.WriteLine("#endif");
         hw.Close();
         
         // run it
         RunIt(files);
      }

      // test if a value is special
      // special values lie in a specific range and are allowed to violate validation rules on parameter values
      bool IsSpecialValue(int spec)
      {
         return (spec <= -16050 && spec > -16100);
      }

      public Form1()
      {
         InitializeComponent();

         // load the keyword table and their meanings
         decodetable["pause"] = 1;
         decodetable["setcolour"] = 2;
         decodetable["setcolor"] = 2;
         decodetable["setallbrightness"] = 3;
         decodetable["adjustbrightness"] = 4;
         decodetable["adjustallbrightness"] = 5;
         decodetable["setcycleinterval"] = 6;
         decodetable["adjustcycleinterval"] = 7;
         decodetable["fadecolour"] = 8;
         decodetable["fadecolor"] = 8;
         decodetable["fadebrightness"] = 9;
         decodetable["donothing"] = 10;
         decodetable["shiftbulbs"] = 11;
         decodetable["rotatebulbs"] = 12;
         decodetable["setfadecolour"] = 13;
         decodetable["setfadecolor"] = 13;
         decodetable["copybulbs"] = 14;
         decodetable["loop"] = 15;
         decodetable["debugbreak"] = 16;
         decodetable["setvariable"] = 17;
         decodetable["adjustvariable"] = 18;
         decodetable["firstbulb"] = 0;
         decodetable["lastbulb"] = 49;
         decodetable["randombulb"] = -16050;
         decodetable["bright"] = 0xCC;
         decodetable["dim"] = 0x66;
         decodetable["off"] = 0x00;
         decodetable["nobrightness"] = -16052;
         decodetable["nocolour"] = -16051;
         decodetable["nocolor"] = -16051;
         decodetable["randomallonecolour"] = -16056;
         decodetable["randomallonecolor"] = -16056;
         decodetable["randomcolours"] = -16057;
         decodetable["randomcolour"] = -16057;
         decodetable["randomcolors"] = -16057;
         decodetable["randomcolor"] = -16057;
         decodetable["randomallonebrightness"] = -16054;
         decodetable["randombrightness"] = -16053;
         decodetable["randomstepcolour"] = -16058;
         decodetable["randomstepcolor"] = -16058;
         decodetable["randomstepbrightness"] = -16055;
         decodetable["red"] = 0xF00;
         decodetable["green"] = 0x0F0;
         decodetable["blue"] = 0x00F;
         decodetable["yellow"] = 0xF80;
         decodetable["orange"] = 0xF20;
         decodetable["purple"] = 0x808;
         decodetable["violet"] = 0x80F;
         decodetable["indigo"] = 0x40C;
         decodetable["black"] = 0x000;
         decodetable["white"] = 0xDDD;
         decodetable["magenta"] = 0xF0F;
         decodetable["cyan"] = 0x0FF;
         decodetable["pink"] = 0xF22;
         decodetable["grey"] = 0x666;
         decodetable["yes"] = 0x01;
         decodetable["no"] = 0x00;

         // load the command table
         commands[1] = new Command("pause", 1, 1, new int[] {1}, new int[] {16000}, new bool[] {true});
         commands[2] = new Command("setcolour", 2, 4, new int[] { 0, 0, -3, -3}, new int[] { 49, 49, 4095, 204}, new bool[] {true, true, true, true});
         commands[3] = new Command("setallbrightness", 3, 1, new int[] { -2 }, new int[] { 204 }, new bool[] {true});
         commands[4] = new Command("adjustbrightness", 4, 3, new int[] { 0, 0, -204 }, new int[] { 49, 49, 204 }, new bool[] {true, true, true});
         commands[5] = new Command("adjustallbrightness", 5, 1, new int[] { -204 }, new int[] { 204 }, new bool[] {true});
         commands[6] = new Command("setcycleinterval", 6, 1, new int[] { 0 }, new int[] { 16000 }, new bool[] {true});
         commands[7] = new Command("adjustcycleinterval", 7, 2, new int[] { -16000, 1 }, new int[] { 16000, 16000}, new bool[] {true, true});
         commands[8] = new Command("fadecolour", 8, 5, new int[] { 0, 0, -2, -2, 1 }, new int[] { 49, 49, 4095, 4095, 16000}, new bool[] {true, true, true, true, true});
         commands[9] = new Command("fadebrightness", 9, 5, new int[] { 0, 0, -2, -2, 1 }, new int[] { 49, 49, 204, 204, 16000 }, new bool[] {true, true, true, true, true});
         commands[10] = new Command("donothing", 10, 1, new int[] { 1 }, new int[] { 16000 }, new bool[] {true});
         commands[11] = new Command("shiftbulbs", 11, 6, new int[] { 0, 0, -48, -4, -4, 1 }, new int[] { 49, 49, 48, 4095, 204, 16000 }, new bool[] {true, true, true, true, true, true});
         commands[12] = new Command("rotatebulbs", 12, 6, new int[] { 0, 0, -48, 1, 0, 0 }, new int[] { 49, 49, 48, 16000, 1, 1 }, new bool[] {true, true, true, true, false, false});
         commands[13] = new Command("setfadecolour", 13, 5, new int[] { 0, 0, -2, -2, -2 }, new int[] { 49, 49, 4095, 4095, 204}, new bool[] {true, true, true, true, true});
         commands[14] = new Command("copybulbs", 14, 6, new int[] { 0, 0, 0, 0, 0, 0 }, new int[] { 49, 49, 49, 49, 1, 1}, new bool[] {true, true, true, true, false, false});
         commands[15] = new Command("loop", 15, 2, new int[] { 0, 1 }, new int[] { 16000, 16000 }, new bool[] {false, true});
         commands[16] = new Command("debugbreak", 16, 1, new int[] { 0 }, new int[] { 16000 }, new bool[] {false});
         commands[17] = new Command("setvariable", 17, 4, new int[] { -16199, -16000, 0, 0 }, new int[] { -16100, 16000, 16000, 1 }, new bool[] {true, true, true, false});
         commands[18] = new Command("adjustvariable", 18, 4, new int[] { -16199, -16000, 0, 0 }, new int[] { -16100, 16000, 16000, 1 }, new bool[] {true, true, true, false});

         // if one or more files were passed in
         if (Environment.GetCommandLineArgs().Count() > 1)
         {
            List<string> ls = new List<string>();

            // look at each argument
            foreach (string s in Environment.GetCommandLineArgs())
            {
               // if it is not the executable
               if (s != Environment.GetCommandLineArgs()[0])
               {
                  string ss = s; // full qualified file name
                  
                  // if the file does not have the full path
                  if (Path.GetDirectoryName(ss) == string.Empty)
                  {
                     // assume it is in the current directory
                     ss = Environment.CurrentDirectory + "\\" + ss;
                  }
                  
                  ls.Add(ss);
               }
            }

            // if one or more files were passed in
            if (ls.Count != 0)
            {
               // compile the files
               CompileFiles(ls.ToArray());

               // start the timer to close this window
               timer1.Interval = 100;
               timer1.Enabled = true;
            }
         }
      }

      private void Form1_DragEnter(object sender, DragEventArgs e)
      {
         // if they are dragging a file
         if (e.Data.GetDataPresent(DataFormats.FileDrop, false) == true)
         {
            // allow them to continue
            e.Effect = DragDropEffects.All;
         }
      }

      // extract a number from a string
      Int16 GetNumber(string s)
      {
            // if it is a hexadecimal number
            if (s.StartsWith("0x") || s.StartsWith("0X"))
            {
               // parse it as a hexadecimal number
               return Int16.Parse(s.Substring(2), System.Globalization.NumberStyles.AllowHexSpecifier);
            }
            else
            {
               // parse it as a regular number
               return Int16.Parse(s);
            }
      }

      Command DecodeCommand(Int16 i)
      {
         // look through the command table for a match
         foreach (KeyValuePair<int, Command> kvp in commands)
         {
            // if found
            if (kvp.Value.Number == i)
            {
               // return the command
               return kvp.Value;
            }
         }
         
         // return nothing
         return null;
      }

      string Decode(string s)
      {
         // check if we know of this keyword
         if (decodetable.ContainsKey(s.ToLower()))
         {
            // we do return it
            return decodetable[s.ToLower()].ToString();
         }
         else
         {
            // we dont so throw an error
            throw new ApplicationException("Unknown string " + s);
         }
      }

      void Compile(string file, int pgm, StreamWriter hw, BinaryWriter bw)
      {
         // open the source file
         StreamReader sr = null;
         try
         {
            sr = new StreamReader(file);
         }
         catch (Exception ex)
         {
            MessageBox.Show("Error opening file " + file + " " + ex.Message);
            throw ex;
         }

         int line = 1; // line in the file ... used in reporting errors
         Int16 command = -1; // current command ... none current right now
         Command com = null; // info about the current command
         int parms = 0; // current parameter being processed

         do
         {
            bool tag = false; // flag if this value is special like a tag

            // read a line
            string s = sr.ReadLine().Trim();

   	    // remove any comment
	    if (s.IndexOf("//") >= 0)
	    {
      		s = s.Substring(0, s.IndexOf("//")).Trim();
	    }

	    foreach(KeyValuePair<string, string> de in defines)
	    {
	    	s = s.Replace("%" + de.Key + "%", de.Value);
	    }

            // if there is something there
            if (s != string.Empty)
            {
               if (s.ToLower().StartsWith("#define "))
               {
                  Regex key = new Regex(" (?'val'[^=]*)=", RegexOptions.Singleline);
                  Regex value = new Regex("=(?'val'[^=]*)$", RegexOptions.Singleline);
                  
                  string k = key.Match(s.ToLower()).Groups["val"].Value;
                  string v = value.Match(s.ToLower()).Groups["val"].Value;
                  defines[k] = v;
                  // stop more processing
                  tag = true;
               }
               // if it starts with a # then it is an include
               else if (s.Substring(0,1) == "#")
               {
                  Compile(s.Substring(1), pgm, hw, bw);
                  tag = true;
               }
               // if it starts with a : then it is a tag
               else if (s.Substring(0, 1) == ":")
               {
                  // check the tag does not start with a number
                  if (char.IsNumber(s, 1))
                  {
                     MessageBox.Show("Tag '"+s+"'not allowed to start with a numeral at line " + line.ToString() + " in " + file);
                  }
                  else
                  {
                     // initialise the tag jump back value
                     tags[s.Substring(1).ToLower()] = 0;
                  }

		  // set the tag flag
                  tag = true;
               }
               else if (command == commands[15].Number && parms == 0)
               {
                  if (char.IsNumber(s, 0))
                  {
                     // already a number ... assume it is ok
                  }
                  else
                  {
                     // if the string is in our list of previously seen tages
                     if (tags.ContainsKey(s.ToLower()))
                     {
                        // get how far to jump back ... need to add one for the iterations
                        int jump = tags[s.ToLower()] + 2;
                        s = jump.ToString().Trim();
                     }
                     else
                     {
                        MessageBox.Show("Tag '" + s + "'not found at line " + line.ToString() + " in " + file);
                     }
                  }
               }
               // if it doeasn't start with a '-' or looks like a number
               else if (s.Substring(0, 1) != "-" && !char.IsNumber(s, 0))
               {
                  try
                  {
                     // decode the keyword
                     s = Decode(s);
                  }
                  catch (Exception ex)
                  {
                     // keyword was not found
                     if (command == -1 || (command != -1 && !com.VarsAllowed(parms)))
                     {
                        MessageBox.Show(ex.Message + " at line " + line.ToString() + " in " + file);
                        return;
                     }
                  }
               }

               // if the command was not a tag
               if (!tag)
               {
                  // if we have no command
                  if (command == -1)
                  {
                     // read the command
                     command = GetNumber(s);

                     // decode the command
                     com = DecodeCommand(command);

	             // increment the jump back value for all tags
                     IncrementTags();

                     // if the command was not valid
                     if (com == null)
                     {
                        // error command not found
                        MessageBox.Show("Unknown command " + command.ToString() + " at line " + line.ToString() + " in " + file);

                        return;
                     }

                     parms = 0; // reset the params count

                     // write out the command
                     bw.Write(command);
                     hw.WriteLine("");
                     hw.Write(command.ToString() + ",");
                  }
                  else
                  {
                     Int16 p = -16300; // our parameter value initialised to an invalid value

                     // if this parameter looks like a number
                     if (s.Substring(0, 1) == "-" || char.IsNumber(s, 0))
                     {
                        // get the parameter value as a number
                        p = GetNumber(s);

    	                // increment the jump back value for all tags
                        IncrementTags();

                        // if the value was less than the minimum for this parameter && not a special value 
                        // ****** PROBLEM ... DOES NOT VALIDATE WHICH SPECIAL VALUES **************
                        if (p < com.Min(parms) && ! IsSpecialValue(p))
                        {
                           // display an error
                           MessageBox.Show("Parameter " + (parms + 1).ToString() + " value " + p.ToString() + " less than minimum " + com.Min(parms) + " on line " + line.ToString() + " in " + file);
                           return;
                        }

                        // if the value was greater than the maximum for this parameter
                        if (p > com.Max(parms))
                        {
                           // display an error
                           MessageBox.Show("Parameter " + (parms + 1).ToString() + " value " + p.ToString() + " greater than maximum " + com.Max(parms) + " on line " + line.ToString() + " in " + file);
                           return;
                        }
                     }
                     else
                     {
                        // this parameter looks like a variable
                        
                        // check if this parameter allows variables
                        if (com.VarsAllowed(parms))
                        {
  	                   // increment the jump back value for all tags
	                   IncrementTags();
        
                           // if the variable is known
	                   if (vars.ContainsKey(s))
                           {
                              // get the variables assigned identifier
                              p = vars[s];
                           }
                           else
                           {
                              // if this is not a set variable command
                              if (command != 17)
                              {
                                 // display an error as we are using an undefined variable
                                 MessageBox.Show("Attempt to use a variable that has not previously been defined " + s + " on line " + line.ToString() + " in " + file);
                                 return;
                              }
                              
                              // allocate the next variable
                              p = __var--;
                              vars[s] = p;
                           }
                        }
                        else
                        {
                           // display an error
                           MessageBox.Show("Attempt to use a variable in a Parameter that does not support them " + (parms + 1).ToString() + " value " + s + " on line " + line.ToString() + " in " + file);
                           return;
                        }
                     }

                     if (p == -16300)
                     {
                        // display an error
                        MessageBox.Show("Error reading parameter for " + (parms + 1).ToString() + " value " + s + " on line " + line.ToString() + " in " + file);
                        return;
                     }

                     // write out the parameter
                     bw.Write(p);
                     hw.Write(p.ToString() + ",");

                     // move onto the next parameter
                     parms++;

                     // if we are out of paramters for this command
                     if (parms >= com.Parameters)
                     {
                        // clear the current command
                        command = -1;
                        com = null;
                        parms = 0;
                     }
                  }
               }
            }

            // increment the line count
            line++;
            
         } while (!sr.EndOfStream); // not end of file

         sr.Close();
      }

      void GELightsCompiler(string file, int pgm, StreamWriter hw)
      {
         string output = Path.GetDirectoryName(file) + "\\" + Path.GetFileNameWithoutExtension(file) + ".dat"; // the binary output file

         try
         {
            // delete any existing file
            if (File.Exists(output))
            {
               File.Delete(output);
            }
         }
         catch (Exception ex)
         {
            MessageBox.Show("Error deleting file " + output + " " + ex.Message);
            throw ex;
         }

         // open the output files
         BinaryWriter bw;

         try
         {
            bw = new BinaryWriter(File.Create(output));
         }
         catch (Exception ex)
         {
            MessageBox.Show("Error opening file " + output + " " + ex.Message);
            throw ex;
         }
         hw.WriteLine("#ifdef PC");
         hw.WriteLine("short program" + pgm.ToString().Trim() +"[] = {");
         hw.WriteLine("#else");
         hw.WriteLine("prog_int16_t program" + pgm.ToString().Trim() + "[] PROGMEM = {");
         hw.WriteLine("#endif");

         Compile(file, pgm, hw, bw);

         // terminate with a -1
         bw.Write((Int16)(-1));

         // temrinate with a -1
         hw.WriteLine("");
         hw.WriteLine("-1};");
         
         // close the files
         bw.Close();
      }

      void RunIt(string[] files)
      {
         // check if simulator is running
         Process[] processes = Process.GetProcesses();
         bool found = false;
         foreach (Process p in processes)
         {
            if (p.MainWindowTitle == "GE Color Effects Simulator")
            {
               found = true;
            }
         }

         // if not found
         if (!found)
         {
            // start the simulator
            Process.Start("GELightsSimulator.exe");
            
            // give it a second to start
            Thread.Sleep(1000);
         }

         string parm = string.Empty;

         foreach (string s in files)
         {
            if (parm != string.Empty)
            {
               parm = parm + " ";
            }
            // work out the name of the binary compiled file
            parm = parm + "\"" + Path.GetDirectoryName(s) + "\\" + Path.GetFileNameWithoutExtension(s) + ".dat" + "\"";
         }

         // run the arudino program with the compiled file
         Process.Start(new ProcessStartInfo("GEColorEffects.exe", parm));
      }

      private void Form1_DragDrop(object sender, DragEventArgs e)
      {
         // get the files dropped
         string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

         CompileFiles(files);
      }

      private void timer1_Tick(object sender, EventArgs e)
      {
         // close this program
         Close();
      }

      private void Form1_Load(object sender, EventArgs e)
      {

      }
   }
   
   // represents a command
   class Command
   {
      string _name; // name of the command
      Int16 _number; // command number
      int _parameters; // number of parameters
      int[] _mins; // minimum values of parameters
      int[] _maxs; // maximum values of parameters
      bool[] _varsallowed;

      // create a command
      public Command(string name, Int16 number, int parameters, int[] mins, int[] maxs, bool[] varsallowed)
      {
         // save the values
         _name = name;
         _number = number;
         _parameters = parameters;
         _mins = mins;
         _maxs = maxs;
         _varsallowed = varsallowed;
      }

      // get the command name
      public string Name
      {
         get
         {
            return _name;
         }
      }

      // get the command number
      public Int16 Number
      {
         get
         {
            return _number;
         }
      }
      
      // get the number of parameters
      public int Parameters
      {
         get
         {
            return _parameters;
         }
      }
      
      // get the minimum for a given parameter
      public int Min(int parm)
      {
         return _mins[parm];
      }

      // get the maximum for a given parameter
      public int Max(int parm)
      {
         return _maxs[parm];
      }

      public bool VarsAllowed(int parm)
      {
         return _varsallowed[parm];
      }
   }
}
