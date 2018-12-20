package com.example.sd.myfirstapplication;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import org.w3c.dom.Text;

/**
 * Created by ника on 23.08.2016.
 */
public class CustomAdapter extends ArrayAdapter<String> {

    public CustomAdapter(Context context, String []products) {
        super(context, R.layout.foods_row, products);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        String product = getItem(position);

        LayoutInflater layoutInflater = LayoutInflater.from(getContext());
        View customView = layoutInflater.inflate(R.layout.foods_row , parent , false);

        ImageView imageView = (ImageView)customView.findViewById(R.id.imageView);
        TextView textView = (TextView) customView.findViewById(R.id.textView);

        textView.setText(product);
        if (product.equals("Food and Drink")) {
            imageView.setImageResource(R.drawable.foods_row);
        }
        else
        if(product.equals("Stationery")) {
            imageView.setImageResource(R.drawable.stationery_row);
        }
        else
        if (product.equals("Clothes")) {
            imageView.setImageResource(R.drawable.clothes_row);
        }
        else
        if (product.equals("Passage")) {
            imageView.setImageResource(R.drawable.passage_row);
        }
        else
        if (product.equals("Debts")) {
            imageView.setImageResource(R.drawable.debts_row);
        }
        else
        if (product.equals("Others"))
        {
            imageView.setImageResource(R.drawable.others_row);
        }
        else
        {
            imageView.setImageResource(R.drawable.statistics_row);
        }


        return customView;
    }

}
