# Priority Queue (C 語言實作)

這是我使用 **C 語言** 實作的 **通用 Priority Queue (優先隊列)**，支援任意資料型態並可切換 **Min-Heap / Max-Heap**。  

---

## 功能特性

- 支援任意資料型態（存入items[]裡，為void*）
- 可選擇 **Min-Heap** 或 **Max-Heap**
- 支援從陣列直接建構 Heap (禁止單個插入)
- 提供基本操作：
  - 初始化 `init`
  - 刪除元素 `deletedata`
  - 堆化 `heapify`
  - 取出最大/最小元素 `pop`
  - 從陣列建構 Heap `buildbyarray`

---

## 資料結構定義

```c
typedef enum {
    PQ_MIN_HEAP = 0,
    PQ_MAX_HEAP = 1
} pqtype_t;

typedef int (*cmpf)(const void *, const void *);

typedef struct {
    void **items;    // 儲存元素的陣列
    int capacity;    // 容量
    int size;        // 當前元素數量
    pqtype_t type;   // 優先隊列類型 (Min/Max)
    cmpf cmp;        // 比較函式
} pq_t;
```
---

## 建議編譯指令

- 將pq.c編譯成.o檔：gcc -c src/pq.c -o /build/pq.o
- 編譯成lib：ar rcs lib/libmylib.a build/pq.o 
- 編譯main.c：gcc -g main.c lib/libmylib.a  (-g為方便debug)

---