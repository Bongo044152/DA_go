# 優先佇列 (Priority Queue) 實作

## 功能包含

- **initpq**: 初始化 pq
- **push**: 將元素塞入並以優先級排列
- **pop**: 將優先級最大的元素取出並重新排列
- **deletedata**: 刪除 index 索引並重新排列
- **build_by_array**: 以 array 建構

## 建議編譯指令

(Windows)
### 第一步：將 pq.c 編譯成 .o 檔
```
gcc -c src\pq.c -o \build\pq.o
```
### 第二步：建立靜態函式庫
```
ar rcs lib\libpq.a build\pq.o
```
### 第三步：編譯 main.c 並連結函式庫
```
gcc lib\example.c lib\libpq.a
```
### 第四步：執行程式
```
./a
```

(Linux)
### 第一步：將 pq.c 編譯成 .o 檔
```
gcc -c src/pq.c -o /build/pq.o
```
### 第二步：建立靜態函式庫
```
ar rcs lib/libpq.a build/pq.o
```
### 第三步：編譯 example.c 並連結函式庫
```
gcc lib/example.c lib/libpq.a
```
### 第四步：執行程式
```
./a.out
```