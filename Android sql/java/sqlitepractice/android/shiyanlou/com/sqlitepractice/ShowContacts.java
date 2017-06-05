package sqlitepractice.android.shiyanlou.com.sqlitepractice;

/**
 * Created by lenovo on 2017/5/22.
 */



        import android.app.AlertDialog;
        import android.content.DialogInterface;
        import android.content.Intent;
        import android.database.Cursor;
        import android.os.Bundle;
        import android.support.v7.app.ActionBarActivity;
        import android.view.Menu;
        import android.view.MenuItem;
        import android.view.View;
        import android.widget.Button;
        import android.widget.EditText;
        import android.widget.Toast;

public class ShowContacts extends ActionBarActivity {
    //    int from_Where_I_Am_Coming = 0;
    private DatabaseHelper myDatabaseHelper;
    //声明一个DatabaseHelper对象

    EditText editText_name;
    EditText editText_phone;
    EditText editText_landline;
    //声明三个文本框用于显示联系人的姓名、手机和座机号码

    int idToBeUpdated = 0;
    //什么一个整型变量用于存放待更新联系人的id

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_contact);

        initUI();

        myDatabaseHelper = new DatabaseHelper(this);

        Bundle extras = getIntent().getExtras();

        if(extras !=null)
        {
            int idFromIntent = extras.getInt("id");

            if(idFromIntent>0){
                //means this is the view part not the add contact part.
                Cursor c = myDatabaseHelper.getData(idFromIntent);
                idToBeUpdated = idFromIntent;
                c.moveToFirst();

                String name = c.getString(c.getColumnIndex(DatabaseHelper.CONTACTS_COLUMN_NAME));
                String phone = c.getString(c.getColumnIndex(DatabaseHelper.CONTACTS_COLUMN_PHONE));
                String landline = c.getString(c.getColumnIndex(DatabaseHelper.CONTACTS_COLUMN_LANDLINE));

                if (!c.isClosed())
                {
                    c.close();
                }

                Button button_save = (Button)findViewById(R.id.button_save);
                button_save.setVisibility(View.INVISIBLE);

                editText_name.setText((CharSequence) name);
                editText_name.setFocusable(false);
                editText_name.setClickable(false);

                editText_phone.setText((CharSequence) phone);
                editText_phone.setFocusable(false);
                editText_phone.setClickable(false);

                editText_landline.setText((CharSequence) landline);
                editText_landline.setFocusable(false);
                editText_landline.setClickable(false);
            }
        }
    }

    public void initUI(){
        //初始化各个控件
        editText_name = (EditText) findViewById(R.id.editText_name);
        editText_phone = (EditText) findViewById(R.id.editText_phone);
        editText_landline = (EditText) findViewById(R.id.editText_landline);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // 填充菜单
        Bundle extras = getIntent().getExtras();

        //根据获得的id类型来填充不同类型的菜单项
        if(extras !=null)
        {
            int idFromIntent = extras.getInt("id");
            if(idFromIntent>0){
                getMenuInflater().inflate(R.menu.menu_show_contact, menu);
            }

            else{
                getMenuInflater().inflate(R.menu.menu_main, menu);
            }
        }
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item)
    {

        //菜单项的点击事件响应方法
        super.onOptionsItemSelected(item);
        switch(item.getItemId())
        {
            //根据菜单项来决定文本框是否可编辑
            case R.id.Edit_Contact:

                Button button_save = (Button)findViewById(R.id.button_save);
                button_save.setVisibility(View.VISIBLE);
                editText_name.setEnabled(true);
                editText_name.setFocusableInTouchMode(true);
                editText_name.setClickable(true);

                editText_phone.setEnabled(true);
                editText_phone.setFocusableInTouchMode(true);
                editText_phone.setClickable(true);

                editText_landline.setEnabled(true);
                editText_landline.setFocusableInTouchMode(true);
                editText_landline.setClickable(true);

                return true;
            case R.id.Delete_Contact:

                //使用对话框来提示用户是否真的要删除，具体用法请参考对话框一节的课程
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setMessage(R.string.deleteContact)
                        .setPositiveButton(R.string.yes, new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                myDatabaseHelper.deleteContact(idToBeUpdated);
                                Toast.makeText(getApplicationContext(), "Deleted Successfully", Toast.LENGTH_SHORT).show();
                                Intent intent = new Intent(getApplicationContext(),MainActivity.class);
                                startActivity(intent);
                            }
                        })
                        .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {

                            }
                        });
                AlertDialog alertDialog = builder.create();
                alertDialog.setTitle("Delete Warning");
                alertDialog.show();

                return true;
            default:
                return super.onOptionsItemSelected(item);

        }
    }

    public void onClickSave(View view)
    {
        //SAVE按钮的响应方法
        Bundle extras = getIntent().getExtras();
        //从Intent对象中获得传递的信息
        if(extras !=null)
        {
            //同样，根据得到的id来决定执行哪种操作，通过Toast告知用户操作的结果
            int idFromIntent = extras.getInt("id");
            if(idFromIntent>0){
                if(myDatabaseHelper.updateContact(idToBeUpdated, editText_name.getText().toString(), editText_phone.getText().toString(), editText_landline.getText().toString())){
                    Toast.makeText(getApplicationContext(), "Updated Successfully", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(getApplicationContext(),MainActivity.class);
                    startActivity(intent);
                }
                else{
                    Toast.makeText(getApplicationContext(), "Update Failed", Toast.LENGTH_SHORT).show();
                }
            }
            else{
                if(myDatabaseHelper.insertContact(editText_name.getText().toString(), editText_phone.getText().toString(), editText_landline.getText().toString())){
                    Toast.makeText(getApplicationContext(), "Created Successfully", Toast.LENGTH_SHORT).show();
                }

                else{
                    Toast.makeText(getApplicationContext(), "Create failed", Toast.LENGTH_SHORT).show();
                }
                Intent intent = new Intent(getApplicationContext(),MainActivity.class);
                startActivity(intent);
            }
        }
    }
}

