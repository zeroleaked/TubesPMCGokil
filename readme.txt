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

V
10
1
2
r
100
2
3
G
1
r
100
3
1
r
100
3
4
V
10
4
1
z