using System;
using System.Net;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Net.Sockets;
namespace SampleSerialTest
{
    class Program
    {

        static void Main(string[] args)
        {

            SerialPort serialPort = new System.IO.Ports.SerialPort("COM14", 9600, Parity.None);
            serialPort.DataBits = 8;
            serialPort.Open();
            
            string task = "23";
            Console.WriteLine("Task Length:{0}", task.Length);
            for (int z = 0; z < task.Length; z++)
            {
                byte[] temp = new byte[1];
                temp[0] = (byte)task[z];
                serialPort.Write(temp, 0, 1);
                string done = serialPort.ReadLine();
                Console.WriteLine("{0}: {1}", (char)task[z], done);
            }

            serialPort.Close();
            return;

            //while (true)
            //{
            //    string sURL;
            //    sURL = "http://192.168.0.102:8080/Warehouse/PathRequest";

            //    WebRequest wrGETURL;
            //    wrGETURL = WebRequest.Create(sURL);

            //    WebProxy myProxy = new WebProxy("myproxy", 80);
            //    myProxy.BypassProxyOnLocal = true;

            //    wrGETURL.Proxy = WebProxy.GetDefaultProxy();

            //    Stream objStream;
            //    objStream = wrGETURL.GetResponse().GetResponseStream();

            //    StreamReader objReader = new StreamReader(objStream);

            //    string sLine = "";
            //    int i = 0;
            //    string task = "";
            //    while (sLine != null)
            //    {
            //        i++;
            //        sLine = objReader.ReadLine();
            //        if (sLine != null)
            //        {
            //            task += sLine;
            //            Console.WriteLine(sLine);
            //        }
            //    }
            //    if (task.Equals(""))
            //    {
            //        System.Threading.Thread.Sleep(5000);
            //        continue;
            //    }
                
            //    SerialPort serialPort = new System.IO.Ports.SerialPort("COM14", 9600, Parity.None);
            //    serialPort.DataBits = 8;
            //    serialPort.Open();
            //    task = "2";
            //    Console.WriteLine("Task Length:{0}", task.Length);
            //    for (int z = 0; z < task.Length; z++)
            //    {
            //        byte[] temp = new byte[1];
            //        temp[0] = (byte)task[z];
            //        serialPort.Write(temp,0,1);
            //        string done = serialPort.ReadLine();
            //        Console.WriteLine("{0}: {1}", (char)task[z], done);
            //    }

            //    serialPort.Close();
            //}
        }
    }
}
