package sqlitepractice.android.shiyanlou.com.sqlitepractice;

/**
 * Created by lenovo on 2017/5/22.
 */

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;

public class DatabaseHelper extends SQLiteOpenHelper {

    public static final String DATABASE_NAME = "Shiyanlou.db";
    public static final String CONTACTS_TABLE_NAME = "contacts";
    public static final String CONTACTS_COLUMN_NAME = "name";
    public static final String CONTACTS_COLUMN_LANDLINE = "landline";
    public static final String CONTACTS_COLUMN_PHONE = "phone";

    public DatabaseHelper(Context context)
    {
        super(context, DATABASE_NAME , null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        // 通常在onCreate()方法中进行数据库的建表操作
        db.execSQL(
                "create table contacts (id integer primary key, name text,phone text,landline text)"
        );
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        // 在onUpgrade()方法中执行数据库的升级操作，可以在这里移除或添加表

        db.execSQL("DROP TABLE IF EXISTS contacts");
        onCreate(db);
    }

    public boolean insertContact  (String name, String phone, String landline)
    {
        //自定义的inserContact()方法，用于插入新的联系人数据
        SQLiteDatabase database = this.getWritableDatabase();
        //声明并从当前类获得可写的数据库对象
        ContentValues contentValues = new ContentValues();
        //用于存储数据集的ContentValues对象

        //下面是将一些值放到该对象中
        contentValues.put("name", name);
        contentValues.put("phone", phone);
        contentValues.put("landline", landline);

        database.insert(CONTACTS_TABLE_NAME, null, contentValues);
        //将做好的数据插入到contacts表中

        return true;
        //若插入成功，则返回true
    }

    public Cursor getData(int id){
        //自定义的数据获取方法，根据传入的ID来查询联系人相关信息并返回
        SQLiteDatabase database = this.getReadableDatabase();
        //获得可读的数据库对象

        Cursor c =  database.rawQuery("select * from contacts where id=" + id + "", null);
        //利用游标在数据库中查询指定id的联系人信息

        return c;
        //返回这个游标对象
    }


    public boolean updateContact (Integer id, String name, String phone, String landline)
    {
        //自定义的updateContact()方法，用于更新联系人信息

        SQLiteDatabase database = this.getWritableDatabase();
        //获得可写的数据库对象
        ContentValues contentValues = new ContentValues();
        contentValues.put("name", name);
        contentValues.put("phone", phone);
        contentValues.put("landline", landline);
        database.update("contacts", contentValues, "id = ? ", new String[]{Integer.toString(id)});
        //将数据更新到数据库中，注意这里要将整数类型的id转化一下
        return true;
    }

    public Integer deleteContact (Integer id)
    {
        //自定义的deleteContact()方法，用于删除指定id的联系人
        SQLiteDatabase database = this.getWritableDatabase();
        //获得可写的数据库对象
        return database.delete("contacts",
                "id = ? ",
                new String[] { Integer.toString(id) });

        //返回符合删除条件where语句的影响范围，若失败则返回0
    }

    public ArrayList<String> getAllContacts()
    {
        //自定义的getAllContacts()方法，用于获得联系人的姓名列表
        ArrayList<String> contacts_list = new ArrayList<String>();

        SQLiteDatabase database = this.getReadableDatabase();
        Cursor c =  database.rawQuery("select * from contacts", null);
        c.moveToFirst();
        //将游标移至首行

        while(c.isAfterLast() == false){
            //用isAfterLast()方法来判断游标是否指向最后一列之后的位置，从而知道是否已经把查询结果的所有数据都遍历了一遍

            contacts_list.add(c.getString(c.getColumnIndex(CONTACTS_COLUMN_NAME)));
            //将数据库中根据姓名这个字段获得的字段索引号来获取其中的值，装在列表中
            c.moveToNext();
            //移至下一行，再次读取数据
        }
        return contacts_list;
        //返回获得的联系人列表
    }
}

