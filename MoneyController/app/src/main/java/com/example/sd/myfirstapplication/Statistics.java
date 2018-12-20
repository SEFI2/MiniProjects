package com.example.sd.myfirstapplication;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import org.w3c.dom.Text;

/**
 * Created by ника on 10.09.2016.
 */
public class Statistics extends AppCompatActivity{
    static  void doSomeThing (int position) {
        SQLiteDatabase db = MainActivity.myDBHandler.getWritableDatabase();
        String query = "SELECT * FROM " + MainActivity.myDBHandler.TABLE_PRODUCTS[position] + " WHERE 1";
        Cursor c = db.rawQuery(query, null);

        if (c.moveToFirst()) {
            do {
                int titleCost = Integer.parseInt(c.getString(c.getColumnIndex("productcost")));
                FoodAndDrink.costs[position] += titleCost;
            } while (c.moveToNext());
        }
        c.close();
        db.close();
    }


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.statistics);
        TextView allCosts = (TextView) findViewById(R.id.allCosts);
        TextView totalCost = (TextView) findViewById(R.id.totalCost);

        doSomeThing(0);
        doSomeThing(1);
        doSomeThing(2);
        doSomeThing(3);
        doSomeThing(4);
        doSomeThing(5);



        String st1 = "";
        st1 += "Food and Drink: " + FoodAndDrink.costs[0] + "KRW\n";
        st1 += "Stationery: " + FoodAndDrink.costs[1] + "KRW\n";
        st1 += "Clothes: " + FoodAndDrink.costs[2] + "KRW\n";
        st1 += "Passage: " + FoodAndDrink.costs[3] + "KRW\n";
        st1 += "Debts: " + FoodAndDrink.costs[4] + "KRW\n";
        st1 += "Others: " + FoodAndDrink.costs[5] + "KRW\n";

        int sum = FoodAndDrink.costs[0] +
                FoodAndDrink.costs[1] +
                FoodAndDrink.costs[2] +
                FoodAndDrink.costs[3] +
                FoodAndDrink.costs[4] +
                FoodAndDrink.costs[5];

                allCosts.setText(st1);
        totalCost.setText("Total cost: " + sum + "KRW");
    }

}
