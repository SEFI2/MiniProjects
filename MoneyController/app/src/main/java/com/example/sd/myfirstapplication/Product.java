package com.example.sd.myfirstapplication;

/**
 * Created by ника on 25.08.2016.
 */
public class Product {
    private String _productname;
    private int _productcost;
    private String _date;
    private int _id;

    public Product(String _productname, int _productcost , String _date) {
        this._productname = _productname;
        this._productcost = _productcost;
        this._date = _date;
    }

    public Product (){

    }



    public String get_productname() {
        return _productname;
    }

    public int get_productcost() {
        return _productcost;
    }

    public int get_id() {
        return _id;
    }

    public void set_productname(String _productname) {
        this._productname = _productname;
    }

    public void set_productcost(int _productcost) {
        this._productcost = _productcost;
    }

    public void set_id(int _id) {
        this._id = _id;
    }

    public String get_date() {
        return _date;
    }


    public void set_date(String _date) {
        this._date = _date;
    }
}
