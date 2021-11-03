using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;


public class SerialWithArduino : MonoBehaviour
{
    SerialPort mSerial;
    public string input;


    void Start() {
        mSerial = new SerialPort();
        mSerial.PortName = "COM4";
        mSerial.BaudRate = 250000;
        mSerial.Open();

        // mInput = gameObject.GetComponent<InputField>();
    }


    void Update() {
        // mSerial.Write("X");
    }


    public void ReadStringInput(string str) {
        input = str;
        Debug.Log(input);
        mSerial.Write(input);
    }
}
