# C++常用函数

* ### make_heap()是生成一个堆，大顶堆或小顶堆

  * `make_heap(_RAIter,_RAIter)` 默认生成大顶堆
  * `make_heap(_RAIter,_RAIter,_Compare)` _Compare有两种参数，一种是greater（生成小顶堆），一种是less（生成大顶堆）

* ### push_heap()是向堆中插入一个元素，并且使堆的规则依然成立

  * `push_heap(_RAIter,_RAIter)` 默认为大顶堆
  * `push_heap(_RAIter,_RAIter,_Compare)` _Compare有两种参数，一种是greater（小顶堆），一种是less（大顶堆）
  * 调用push_heap之前必须调用make_heap创建一个堆
  * 首先数组push_back插入元素，然后再调用push_heap，它会使最后一个元素插到合适位置
  * 注意，push_heap中的_Compare和make_heap中的_Compare参数必须是一致的，不然会插入堆失败，最后一个元素还是在最后位置，导致插入失败

* ### pop_heap()是在堆的基础上，弹出堆顶元素

  * `pop_heap(_RAIter,_RAIter)` 默认为大顶堆
  * `pop_heap(_RAIter,_RAIter,_Compare)` _Compare有两种参数，一种是greater（小顶堆），一种是less（大顶堆）
  * 比如`pop_heap(nums.begin(), nums.end(),greater<int>())`，它会将堆顶元素（即为数组第一个位置）和数组最后一个位置对调，然后你可以调用数组pop_back，删除这个元素
  * 注意，pop_heap中的_Compare和make_heap中的_Compare参数必须是一致的，不然会失败

* ```
  升序队列：	priority_queue <int,vector<int>,greater<int> > q;
  ```

* 降序队列：priority_queue <int,vector<int>,less<int> >q;

* sort自定义比较函数

  * ``bool  cmp(int a,int b)

    {

            return b<a;

    }

    sort(a,a+n,cmp);

    传入的参数类型和需要排序的数据类型一致，如果认为第一个参数比第二个小，也就是第一个参数需要排在第二个参数前面时返回true，反之返回 false。系统默认a<b时返回true，于是从小到大排。而上面的例子是当b小于a时，认为a小于b。所以排序的结果就是将元素按从大到小的顺序排序。