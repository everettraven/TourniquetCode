using System;

using System.Collections.Generic;

using System.Linq;

using System.Text;

using System.Threading.Tasks;

using System.IO.Ports;

using System.Threading;



/*

    C# console application written by Bryce Palmer to send
    data to an arduino and the arduino does an action based
    off of the data recieved. Arduino sends back a character to 
    signify the data has been recieved.

 */



namespace BluetoothForTourniquet

{

    class Program

    {

        static void Main(string[] args)

        {

            try

            {

                string[] Ports;

                string input;

                Console.WriteLine("Welcome to the Bluetooth COM Port for the Secret Project");

                Console.WriteLine("------------------------------------------------------------------");

                SerialPort serial = new SerialPort();

                Ports = SerialPort.GetPortNames();



                Console.WriteLine("Available Ports");

                Console.WriteLine("------------------------------------------------------------------");



                for (int i = 0; i < Ports.Length; i++)

                {

                    Console.WriteLine(Ports[i]);

                }

                Console.WriteLine("Type which port you want to connect to");

                input = Console.ReadLine();

                Console.WriteLine();



                serial.PortName = input;

                serial.BaudRate = 9600;

                serial.Parity = Parity.None;

                serial.DataBits = 8;

                serial.StopBits = StopBits.One;

                serial.Open();

                while (true)
                {
                    Console.WriteLine("Type the command you would like to run. I (capital i) = Turn on, O = Turn off, E = exit, to change PWM and interval value do as follows -------------> PWMValue:Interval");
                    string SendData = Console.ReadLine();

                    if(SendData.Contains(":"))
                    {
                        serial.Write(SendData);
                        break;
                    }
                    else if(SendData == "I")
                    {
                        serial.Write(SendData);
                        break;
                    }
                    else if(SendData == "O")
                    {
                        serial.Write(SendData);
                        break;
                    }
                    else if (SendData == "E")
                    {
                        break;
                    }
                    else
                    {
                        Console.Write("That input is invalid");
                    }

                }


               serial.DataReceived += new SerialDataReceivedEventHandler(Serial_DataReceived);


                Console.WriteLine("Press any key to quit");
                Console.ReadKey();

                serial.Close();



            }

            catch (Exception e)

            {

                Console.WriteLine(e.Message);

                Console.ReadKey();

            }



        }



        private static void Serial_DataReceived(object sender, SerialDataReceivedEventArgs e)

        {

            SerialPort sp = (SerialPort)sender;

            string Output = sp.ReadExisting();

            Console.WriteLine(Output);

        }

    }

}