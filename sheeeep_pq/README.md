# 優先佇列 (Priority Queue) 實作

## 功能包含

- **initpq**: 初始化 pq
- **push**: 將元素塞入並以優先級排列
- **pop**: 將優先級最大的元素取出並重新排列
- **deletedata**: 刪除 index 索引並重新排列
- **build_by_array**: 以 array 建構

## 運行指令

```
(Windows)
gcc -c src\pq.c -o \build\pq.o
ar rcs lib\libpq.a build\pq.o
gcc lib\example.c lib\libpq.a
./a

(Linux)
gcc -c src/pq.c -o /build/pq.o
ar rcs lib/libpq.a build/pq.o
gcc lib/example.c lib/libpq.a
./a.out
```