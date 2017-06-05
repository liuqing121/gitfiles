package sqlitepractice.android.shiyanlou.com.sqlitepractice;



        import android.content.Intent;
        import android.os.Bundle;
        import android.support.v7.app.ActionBarActivity;
        import android.view.Menu;
        import android.view.MenuItem;
        import android.view.View;
        import android.widget.AdapterView;
        import android.widget.AdapterView.OnItemClickListener;
        import android.widget.ArrayAdapter;
        import android.widget.ListView;

        import java.util.ArrayList;

public class MainActivity extends ActionBarActivity {
    private ListView listView;
    //声明一个ListView对象
    DatabaseHelper myDatabaseHelper;
    //声明一个DatabaseHelper对象

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //在onCreate方法中设置好页面的布局，初始化要用到的控件
        initUI();

    }

    public void initUI() {
        //实例化这个列表，并初始化数据
        listView = (ListView)findViewById(R.id.listView_contacts);
        initData();
    }

    public void initData() {
        myDatabaseHelper = new DatabaseHelper(this);
        //实例化这个DatabaseHelper对象

        ArrayList<String> array_list = myDatabaseHelper.getAllContacts();
        //获取所有联系人的信息，放入ArrayList中待用
        ArrayAdapter arrayAdapter=new ArrayAdapter<>(this,android.R.layout.simple_list_item_1, array_list);
        //做一个ArrayAdapter适配器用于向列表填充数据


        listView.setAdapter(arrayAdapter);
        //设定列表的填充器为刚刚创建的这个arrayAdapter

        listView.setOnItemClickListener(new OnItemClickListener() {
            @Override
            //为列表项添加点击事件监听器
            public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
                //在响应方法中设置跳转到相应的联系人详情页
                int id_contacts = arg2 + 1;
                //将联系人的ID与列表项的ID匹配起来

                Bundle dataBundle = new Bundle();
                dataBundle.putInt("id", id_contacts);
                //声明一个Bundle对象，用于传递

                Intent intent = new Intent(getApplicationContext(), ShowContacts.class);
                //声明一个Intent对象，用于跳转到联系人的详情页
                intent.putExtras(dataBundle);

                startActivity(intent);
                //设定好跳转所需的数据后，跳转到详情页
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //将菜单的布局填充进来，从而在ActionBar的右侧点开菜单按钮你就可以看到菜单项
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item){
        super.onOptionsItemSelected(item);

        //设置菜单项的点击事件响应方法
        //根据获取到的菜单项id来执行响应的处理
        switch(item.getItemId())
        {
            case R.id.item_add:
                Bundle bundle = new Bundle();
                bundle.putInt("id", 0);
                //将菜单项的id放入Bundle对象中，传递至下一个Activity

                Intent intent = new Intent(getApplicationContext(),ShowContacts.class);
                intent.putExtras(bundle);

                startActivity(intent);
                //执行Activity跳转
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        initData();
        //之所以在onResume也要初始化数据的目的为了刷新列表
        //你可以使用notifyDatasetChanged()方法来替代这一步
    }
}

