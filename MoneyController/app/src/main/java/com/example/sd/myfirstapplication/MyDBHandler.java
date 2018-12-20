package com.example.sd.myfirstapplication;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.ArrayList;

/**
 * Created by ника on 15.08.2016.
 */

public class MyDBHandler extends SQLiteOpenHelper{
    private static  int DATABASE_VERSION = 2;
    private static  final  String DATABASE_NAME = "hahahaname.db";
    public static  String TABLE_PRODUCTS[] = {"FoodandDrink" , "Stationery" , "Clothes" , "Passage" , "Debts" , "Others"};
    private static final String COLUMN_ID = "_id";
    public  static final String COLUMN_PRODUCTNAME = "productname";
    public static final String COLUMN_PRODUCTCOST = "productcost";
    public static final String COLUMN_PRODUCTDATE = "productdate";

    public MyDBHandler(Context context, String name, SQLiteDatabase.CursorFactory factory, int version) {
        super(context, DATABASE_NAME, factory, DATABASE_VERSION);
    }


    @Override
    public void onCreate(SQLiteDatabase db) {
        for (int i = 0 ; i < 6 ; ++i)doCreate(db , i);
    }

    public void doCreate (SQLiteDatabase db , int pos) {
        String query = "CREATE TABLE " + TABLE_PRODUCTS[pos] + " ( "
                + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT , "
                + COLUMN_PRODUCTNAME + " TEXT, "
                + COLUMN_PRODUCTCOST + " INTEGER, "
                + COLUMN_PRODUCTDATE + " TEXT);";
        db.execSQL(query);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int i, int i1) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_PRODUCTS[0]);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_PRODUCTS[1]);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_PRODUCTS[2]);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_PRODUCTS[3]);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_PRODUCTS[4]);
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_PRODUCTS[5]);
        onCreate(db);
    }


    // add a new raw to the database
    public void addProduct (Product product , int position) {
        ContentValues values = new ContentValues();
        values.put(COLUMN_PRODUCTNAME , product.get_productname());
        values.put(COLUMN_PRODUCTCOST , product.get_productcost());
        values.put(COLUMN_PRODUCTDATE , product.get_date());
        SQLiteDatabase db = getWritableDatabase();
        db.insert(TABLE_PRODUCTS[position] , null , values);
        db.close();
    }






}



























