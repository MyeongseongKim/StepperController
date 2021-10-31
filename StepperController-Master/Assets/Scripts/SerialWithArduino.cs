using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;


public class SerialWithArduino : MonoBehaviour
{
    SerialPort stream;

    void Start() {
        stream = new SerialPort();
        stream.PortName = "COM1";
        stream.BaudRate = 9600;
        stream.Open();
    }


    void Update() {
        stream.Write("X");
    }
}
