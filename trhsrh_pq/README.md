# Priority Queue

這份專案是由 明哲(trshrh) 實作的 **Priority Queue 資料結構的 Library**，使用侵入式結構可支援儲存符合**限定規範**的資料存入並被操作，且實作基本功能可供使用者 include 後使用。

---
### 結構體介紹：

1. ``List_t``：

    List_t 為此專案中**侵入式結構**的結構體名稱，以下是 List_t 的結構：
    ```C
    typedef struct List_t {
        int priority;
    } List_t;
    ```
    只要插入的資料的結構是以 int priority 為結構體中的第一個資料即符合規範可支援。

2. ``PQ_mode``：

    PQ_mode 為 enum 用於判定 priorityqueue 當前是**以大至小 (Max) 或是以小至大 (Min) 排序**，以下是 PQ_mode 的結構：
    ```C
    typedef enum PQ_mode {
        Max,
        Min
    }PQ_mode;
    ```

3. ``PriorityQueue``：

    PriorityQueue 為專案中主角 priorityqueue 物件的結構，以下是 PriorityQueue 結構：
    ```C
    typedef struct PriorityQueue{
        PQ_mode mode;
        int capacity;
        int size;
        List_t** container;
    } PriorityQueue;
    ```
    其中：
    1. ``PQ_mode mode``：mode 控制 priorityqueue 物件的模式。 
    2. ``int capacity``：capacity 為 priorityqueue 物件當前的容量上限。
    3. ``int size``：size 用於代表 priorityqueue 當前的物件數量。
    4. ``List_t** container``：container 為 priorityqueue 物件管理資料的容器。


---
### Priority Queue 功能介紹：

此 Priority Queue 實作提供以下功能：

- ``PQ_create``
- ``PQ_create_with_array``
- ``PQ_switch_mode``
- ``PQ_push``
- ``PQ_pop``

以下介紹各個函式：

_PS：該專案中的資料使用侵入式結構 List_t，可支援符合 List_t 的資料插入，**意即只要資料符合 List_t 使用皆可被插入 priorityqueue 物件中**，不受接收參數為 List_t 影響。_

 1. ``PQ_create``：
    - 函式功能簡介：呼叫該函式可用於建構一個被賦值為空的 priority queue 物件並被回傳。
    - 函式接收參數：PQ_mode mode
    - 函式回傳參數：PriorityQueue* priorityqueue

2. ``PQ_create_with_array``：
    - 函式功能簡介：呼叫該函式可將已有的陣列傳入並生成 priority queue 物件並被回傳。
    - 函式接收參數：List_t** array,  int size, PQ_mode mode
    - 函式回傳參數：PriorityQueue* priorityqueue
    - PS：傳入參數中的 size 為傳入陣列的大小。

3. ``PQ_switch_mode``：
    - 函式功能簡介：呼叫該函示可將指定的 priorityqueue 轉為指定的模式 (PQ_mode)。
    - 函式傳入參數：PriorityQueue* priorityqueue, PQ_mode mode
    - 函式回傳參數：無。

4. ``PQ_push``：
    - 函式功能簡介：呼叫該函式可將指定的 node 加入指定的 priorityqueue 中。
    - 函式傳入參數：PriorityQueue* priorityqueue, List_t* node
    - 函式回傳參數：無

5. ``PQ_pop``：
    - 函式功能簡介：呼叫該函式會將指定 priorityqueue 中 priority 最高的物件取出並回傳。
    - 函式傳入參數：PriorityQueue* priorityqueue
    - 函式回傳參數：List_t* node

---
### Makefile 使用指南：

Makefile 可以簡化專案的編譯以及執行檔生成。以下為 Makefile 指令：

_PS：_ Makefile 在 Linix 核心的作業系統中才可使用。

1. ``make``
2. ``make run_example_basic``
3. ``make run_example_advance``
4. ``make clean``

以下是各指令介紹：

1. ``make``：在終端機輸入該指令可直接編譯 ``source file`` 以及 ``example`` 檔案，產生的 ``.o`` 及 ``.out`` 檔會被儲存在 ``build`` 資料夾中，若沒 ``build`` 資料夾將自動生成。

2. ``make run_example_basic``：在終端機輸入該指令可執行 ``example_basic.out`` 檔，若無該檔案將自行編譯並生成於 ``build`` 資料夾中，若沒 ``build`` 資料夾將自動生成。

3. ``make run_example_advance``：在終端機輸入該指令可執行 ``example_advance.out`` 檔，若無該檔案將自行編譯並生成於 ``build`` 資料夾中，若沒 ``build`` 資料夾將自動生成。

4. ``make clean``：在終端機輸入該指令可將 ``build`` 資料夾以及其中檔案一併刪除。

---
### 作者：

trhsrh (Justin0326)