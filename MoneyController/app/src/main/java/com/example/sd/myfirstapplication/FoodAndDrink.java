package com.example.sd.myfirstapplication;

import android.content.DialogInterface;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;
import java.util.concurrent.ExecutionException;

public class FoodAndDrink extends AppCompatActivity{
        String linkType;
        Button addProduct;
        ArrayAdapter<String> listAdapter;
        ArrayList <String> arrayList;
        ArrayList <String> arrayName;
        ArrayList <Integer> arrayCost;
        ArrayList <String> arrayDate;
        TextView mediumText;

    ListView listView;
        TextView textView;
        static int [] costs = new int[6];
        int position;
        static  int counter = 0;

        @Override
        protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_food_and_drink);

            linkType = getIntent().getExtras().getString("messageK");
            textView = (TextView) findViewById(R.id.textView2);
            if (linkType.equals("Food and Drink"))position = 0;
            else if(linkType.equals("Stationery"))position = 1;
            else if(linkType.equals("Clothes"))position = 2;
            else if (linkType.equals("Passage")) position = 3;
            else if (linkType.equals("Debts"))position = 4;
            else position = 5;
            mediumText = (TextView)findViewById(R.id.mediumText);


            textView.setText(linkType);


            arrayList = new ArrayList<String>();
            arrayCost = new ArrayList<Integer>();
            arrayName = new ArrayList<String>();
            arrayDate = new ArrayList<String>();

            listAdapter = new ArrayAdapter<String>(this , android.R.layout.simple_list_item_1 , arrayList);

            listView = (ListView) findViewById(R.id.foodListView);
            listView.setAdapter(listAdapter);

            registerForContextMenu(listView);

            addProduct = (Button) findViewById(R.id.addItemButton);
            addProduct.setOnClickListener(
                    new View.OnClickListener() {
                        @Override
                        public void onClick(View view) {
                            addItem();
                        }
                    }
            );

            costs[position] = 0;
            updateAll();
            mediumText.setText(costs[position] + "KRW");

        }

        private void updateAll () {
            databaseToString(-1);
        }



        public void addItem () {
            AlertDialog.Builder alertDialog = new AlertDialog.Builder(FoodAndDrink.this);
            alertDialog.setTitle("Adding product");
            LinearLayout layout = new LinearLayout(FoodAndDrink.this);

            final EditText name = new EditText(FoodAndDrink.this);
            LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(
                    300,
                    120
            );

            name.setLayoutParams(lp);
            name.setHint("Name");

            final EditText cost = new EditText(FoodAndDrink.this);
            cost.setLayoutParams(lp);
            cost.setHint("Cost");

            layout.addView(name);
            layout.addView(cost);


            alertDialog.setView(layout);


            alertDialog.setPositiveButton("OK",
                    new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                            try {
                                String titleName = name.getText().toString().toUpperCase();
                                int titleCost = Integer.parseInt(cost.getText().toString());
                                String date = (new SimpleDateFormat("hh:mm:ss , dd/MM/yyyy", Locale.ITALY)).format(new Date());

                                Product product = new Product(titleName, titleCost, date);
                                MainActivity.myDBHandler.addProduct(product, position);

                                arrayList.add(titleName + "   " + titleCost + "KRW\n" + date);
                                listAdapter.notifyDataSetChanged();

                                arrayName.add(titleName);
                                arrayCost.add(titleCost);
                                arrayDate.add(date);
                                costs[position] += titleCost;
                                mediumText.setText(costs[position] + "KRW");

                            }
                            catch (Exception e) {
                                Toast.makeText(FoodAndDrink.this, "Please, enter all information correctly" , Toast.LENGTH_SHORT).show();

                            }
                        }
                    }
            );
            alertDialog.show();
        }
    public void databaseToString (int _position)
        {
            if(_position != -1)position = _position;

            SQLiteDatabase db = MainActivity.myDBHandler.getWritableDatabase();
            String query = "SELECT * FROM " + MainActivity.myDBHandler.TABLE_PRODUCTS[position] + " WHERE 1";


            Cursor c = db.rawQuery(query, null);

            if (c.moveToFirst()) {
                do {
                    String titleName = c.getString(c.getColumnIndex("productname"));
                    int titleCost = Integer.parseInt(c.getString(c.getColumnIndex("productcost")));
                    String date = c.getString(c.getColumnIndex("productdate"));

                    arrayList.add(titleName + "      " + titleCost + "KRW\n" + date);
                    listAdapter.notifyDataSetChanged();
                    costs[position] += titleCost;
                    arrayName.add(titleName);
                    arrayCost.add(titleCost);
                    arrayDate.add(date);

                } while (c.moveToNext());
            }
            c.close();
            db.close();
        }
    public void onCreateContextMenu (ContextMenu menu , View v, ContextMenu.ContextMenuInfo menuInfo) {
        if (v.getId() == R.id.foodListView) {
            AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo)menuInfo;
            menu.setHeaderTitle(arrayName.get(info.position));
            menu.add("DELETE");
        }
    }

    public boolean onContextItemSelected(MenuItem item) {
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();

        SQLiteDatabase db = MainActivity.myDBHandler.getWritableDatabase();
        try {
            boolean i = db.delete(MainActivity.myDBHandler.TABLE_PRODUCTS[position], MainActivity.myDBHandler.COLUMN_PRODUCTDATE + "='" + arrayDate.get(info.position)+"'", null) > 0;
        }
        catch (Exception e){
            textView.setText(e.toString());
        }
        costs[position] -= arrayCost.get(info.position);
        mediumText.setText(costs[position] + "KRW");

        arrayList.remove(info.position);
        arrayName.remove(info.position);
        arrayCost.remove(info.position);
        arrayDate.remove(info.position);
        listAdapter.notifyDataSetChanged();
        return true;
    }
}








