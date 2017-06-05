package net.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
//import android.support.test.*;
import udp.net.R;
import android.widget.Toast;

public class UDPActivity extends Activity {
    /** Called when the activity is first created. */

    //收发用同一个socket	，只在连接时实例化一次
    private DatagramSocket socketUDP=null;
    private Thread    thread=null;     //接收线程
    private Thread    th_send=null;    //发送线程
    private TextView  textSend;
    private TextView  textReceive;
    private TextView  portRemote;
    private TextView  portLocal;
    private TextView  textIP;
    private Button    btnSend;
    private Button    btnConnect;
    private Button    btnDisConnect;
    private Button btnClear;
    private int       portRemoteNum;
    private int       portLocalNum;
    private String    addressIP;
    private String    revData;
    private boolean   flag=false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //与UI关联
        textSend = (TextView)findViewById(R.id.textsend);
        textReceive = (TextView)findViewById(R.id.textrcecive);
        textIP = (TextView)findViewById(R.id.textip);
        portRemote = (TextView)findViewById(R.id.textPortRemote);
        portLocal = (TextView)findViewById(R.id.textPortLocal);
        btnSend = (Button) findViewById(R.id.btnsend);
        btnSend.setEnabled(false);
        btnConnect = (Button) findViewById(R.id.btnconnect);
        btnDisConnect = (Button) findViewById(R.id.btndisconnect);
        btnClear = (Button) findViewById(R.id.btnclear);
        btnDisConnect.setEnabled(false);

        buttonAction();

        textSend.setText("lq");
        textIP.setText("192.168.0.10");
        portRemote.setText("8080");
        portLocal.setText("8080");
    }

    //设置按键监听及动作
    public void buttonAction(){
        btnSend.setOnClickListener(new OnClickListener() {//发送按钮
            public void onClick(View v) {
                // TODO Auto-generated method stub
                //sendData();	//错误：主线程执行，导致android4发送不出去
                //启动发送线程
                th_send = new Thread(sendMsg);
                th_send.start();
            }
        });

        btnConnect.setOnClickListener(new OnClickListener() {//连接按钮
            public void onClick(View v) {
                // TODO Auto-generated method stub
                try{
                    flag=true;
                    portRemoteNum=Integer.parseInt(portRemote.getText().toString());
                    portLocalNum=Integer.parseInt(portLocal.getText().toString());
                    addressIP = textIP.getText().toString();
                    //用设定的本地端口发数据，这样PC解析出来的端口号就在断开前不会变化
                    socketUDP = new DatagramSocket(portLocalNum);
                    // 启动接收线程，用本地端口接收,因为本地端口和PC解析出来端口的对应
                    thread = new Thread(revMsg);
                    thread.start();
                    btnConnect.setEnabled(false);
                    btnDisConnect.setEnabled(true);
                    btnSend.setEnabled(true);

                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }

            }
        });

        btnDisConnect.setOnClickListener(new OnClickListener() {//断开按钮
            public void onClick(View v) {
                // TODO Auto-generated method stub
                flag=false;//结束线程
                socketUDP.close();
                btnConnect.setEnabled(true);
                btnDisConnect.setEnabled(false);
                btnSend.setEnabled(false);
            }
        });

        btnClear.setOnClickListener(new OnClickListener() {//清空按钮
            public void onClick(View v) {
                // TODO Auto-generated method stub
                textReceive.setText("");
            }
        });
    }

    //发送udp数据包必须在子线程
    void sendData()
    {
        try {

            InetAddress serverAddress = InetAddress.getByName(addressIP);
            String str = textSend.getText().toString();
            byte data [] = str.getBytes();
            DatagramPacket packetS = new DatagramPacket(data,
                    data.length,serverAddress,portRemoteNum);
            //从本地端口给指定IP的远程端口发数据包
            socketUDP.send(packetS);
        } catch (Exception e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }

    //接收子线程数据，并修改界面
    private Handler handler = new Handler()
    {
        @Override
        public void handleMessage(Message msg)
        {
            if (textReceive != null)
            {
                if (revData==null) return;
                StringBuilder sb = new StringBuilder();
                sb.append(textReceive.getText().toString().trim());
                sb.append(" ");
                sb.append(revData);
                textReceive.setText(sb.toString().trim());
                sb.delete(0, sb.length());
                sb = null;
            }
        }
    };

    private Runnable revMsg = new Runnable() {
        @Override
        public void run()
        {
            while (flag)
            {
                byte data[] = new byte[1024];
                DatagramPacket packetR = new DatagramPacket(data, data.length);
                try {
                    socketUDP.receive(packetR);
                    revData = new String(packetR.getData(),
                            packetR.getOffset(),packetR.getLength());
                    handler.sendEmptyMessage(0);
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    };


    private Runnable sendMsg = new Runnable() {
        @Override
        public void run()
        {
            sendData();
        }

    };



    //退出提示
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        if (keyCode == KeyEvent.KEYCODE_BACK && event.getRepeatCount() == 0) {

            AlertDialog alertDialog = new AlertDialog.Builder(
                    UDPActivity.this).setTitle("退出程序").setMessage("是否退出程序")
                    .setPositiveButton("确定",
                            new DialogInterface.OnClickListener() {

                                public void onClick(DialogInterface dialog,
                                                    int which) {
                                    android.os.Process.killProcess(
                                            android.os.Process.myPid());
                                }

                            })
                    .setNegativeButton("取消",
                            new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int which) {
                                    return;
                                }
                            }).create(); // 创建对话框

            alertDialog.show(); // 显示对话框

            return false;
        }

        return false;
    }
}

