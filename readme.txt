done :
1. struct (if needed going to be added)
2. print in debug except printNode
3. every make except makeNode has been tested
4. in input.h, every procedure except pushresToNodeArray is not tested
5. Matrices sudah dicoba, tinggal bagian adjoin


to do :
0. Print node dicoba juga dulu
1. Bagian input pushresToNodeArray belum dicoba
    dicoba dulu
2. if 1 done, please make another push for res, ind, cap, volt and current



Cara membaca : 
1. configuration untuk semua typedef
    tab untuk array, Neff adalah jumlah isinya
2. debug untuk Print
3. procedure untuk berbagai procedure untuk struct
    untuk inisiasi tab, gunakan initiate sesuai dengan masukannya
    untuk memasukkan ke tab, gunakan addTo


Run
gcc main.c Configuration/procedure.c HashMap/hashMap.c Input/input.c Matrices/matrices.c Model/model.c -o a
pakai yang ini cam
Test 
V
10
1
0
r
100
1
0
G
0
z
0
10

V
10
2
1
r
1
3
2
r
1
1
3
G
1
z
0
10

V
10
2
1
r
1
3
2
r
4
4
3
A
1
3
4
G
4
G
1
z

G
0
V
10
1
0
V
20
3
1
V
5
9
5
V
10
5
8
r
10000
2
1
r
5000
4
2
r
1000
5
2
r
5000
6
4
r
3000
8
6
r
4000
5
3
r
1000
9
0
z
0
10