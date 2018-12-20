package com.example.sd.myfirstapplication;

import android.content.ContentValues;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.ListViewCompat;
import android.view.ContextMenu;
import android.view.View;
import android.webkit.WebView;
import android.widget.AdapterView;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.util.ArrayList;


public class MainActivity extends AppCompatActivity{

    static MyDBHandler myDBHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        WebView webView = (WebView) findViewById(R.id.webView);
        webView.loadUrl("D:\\Csacademy.html");

        myDBHandler = new MyDBHandler(getApplicationContext() , null , null , 1);

        ArrayList<String> arrayList = new ArrayList<String>();

        String [] products = {"Food and Drink" , "Stationery" , "Clothes" , "Passage" , "Debts" , "Others" , "Statistics"};
        ListAdapter listAdapter = new CustomAdapter(this , products);
        ListView listView = (ListView) findViewById(R.id.listView);
        listView.setAdapter(listAdapter);

        listView.setOnItemClickListener(
                new AdapterView.OnItemClickListener() {
                    @Override
                    public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                        if(i != 6) {
                            Intent intent = new Intent(MainActivity.this, FoodAndDrink.class);
                            intent.putExtra("messageK", String.valueOf(adapterView.getItemAtPosition(i)));
                            startActivity(intent);
                        }
                        else {
                                Intent intent = new Intent(MainActivity.this, Statistics.class);
                                startActivity(intent);
                        }
                    }
                }
        );


    }

}
