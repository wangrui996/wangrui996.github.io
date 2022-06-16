
# 机考题目收集  

[牛客华为题目](https://www.nowcoder.com/exam/oj/ta?tpId=37)  



# 5.18机考  

## 1.扑克牌排序(100分) 

一副扑克牌去掉大小王，数值大小为从1到13（1>13），花色大小为从4到1(1<4)；
炸弹大于对子，对子大于单张，同样数值按花色大小排序
若一个数值有三张，则花色小的两张组成对子，花色大的组成单张
时间限制1000ms

输入：
第一行为扑克牌总数
后面每行为 “花色 大小”

输出：
按顺序，先输出所有炸弹，再输出所有对子，最后输出所有单张
例如：
1 2 炸弹
2 2
3 2
4 2
1 1 对1
3 1
4 1 单张1
1 3 单张3
3 6 单张6
4 13 单张13


## 2.宝藏位置(200分)   

输入：
1行： “m n”，m为地图行数，n为地图列数
2~m+1行 长度为n的字符串，为每格地形
m+2行： ‘x y’，x为宝藏初始横坐标，y为宝藏初始纵坐标
m+3行： “number” 行动次数

时间限制2000ms
字符串有六种字符，各自为
'.'空地，到达此处后不会再更改位置
'#'障碍，无法到底此处，若目的地障碍处则不移动
'^'向上走
'v'向下走
'<'向左走
'>'向右走
宝藏不会超出边界，若下一步超出边界则停留在原位置

输出：
宝藏最终位置

**示例：**

    "3 4"

    ">>v."
    ">v<>"
    "#.><"

    "0 0"
    "10000"
    输出：
    2 1  





# 5.11机考 

[力扣链接](https://leetcode.cn/circle/discuss/k99FWy/)
## 1.小孩子分糖果游戏（100分） 

一个数组n(1<=n<=100000)个小孩，每个小孩抽到一张卡片，每个小孩要给右边卡片数字比自己小的人分一颗糖果，问每个小孩分糖果的数量，保证每张卡片数字不一样。
（其实就是统计数组右边比自己小的元素个数）
例如：
输入：8 7 9 5 2
输出: 3 2 2 1 0


## 2.围棋活子个数 （200分）
定义棋盘大小1<=n<=19.定义围棋上下左右的且没棋子的地方为“眼”的个数，如果一组棋子是同一个颜色，那么共用“眼”。一组棋子就是上下左右相连的棋子，斜着的不算。
W为白子，B为黑子，N为没有棋子，例如
NNNN
NBBN
NNBN
NNNN
这组黑子的“眼”个数为7.
NNN
BWB
NBN
这里白子的“眼”个数为1，因为只有上面是空的，下左右都有子了。

定义只有眼>=2的子为活子。求围棋盘黑子和白子活子的个数。
例:
输入： 3WWWNBBBNN
输出： B 3 W 0

解释：棋盘
W W W
N B B
B N N
三个W的眼为1，死子。2个B的眼为3，1个B的眼为2。都是活子。

dfs

```cpp
    def fun():
    inputS = input()
    # 棋盘大小
    N = int(inputS[0])
    inputS = inputS[1:]
    matChess = []
    offset = [[-1, 0], [0, -1], [1, 0], [0, 1]]
    # 记录黑白每个位置的气
    dictC = {'B': 0, 'W': 0}
    # 黑白棋的搜索
    visited = [[0 for _ in range(N)] for _ in range(N)]
    for i in range(N):
        matChess.append([inputS[i * N + j] for j in range(N)])

    def dfs(k, j, WOB):
        visited[k][j] = 1
        for order in offset:
            x = k + order[0]
            y = j + order[1]
            if 0 <= x < N and 0 <= y < N and not visited[x][y]:
                if matChess[x][y] == WOB:
                    live_and_num[1] += 1
                    dfs(x, y, WOB)
                elif matChess[x][y] == 'N' and not visitedN[x][y]:
                    visitedN[x][y] = 1
                    live_and_num[0] += 1

    for i in range(N):
        for j in range(N):
            if matChess[i][j] != 'N' and not visited[i][j]:
                # 棋子气数==相邻棋子数气数之和-公共的气
                live_and_num = [0, 1]
                # 同一个联通量中，周围气的搜索
                visitedN = [[0 for _ in range(N)] for _ in range(N)]
                dfs(i, j, matChess[i][j])
                if live_and_num[0] >= 2:
                    dictC[matChess[i][j]] += live_and_num[1]
    print('B ' + str(dictC['B']) + ' W ' + str(dictC['W']))
    return


if __name__ == '__main__':
    fun()
    # 3WWWNBBBNN
    # 5NNWBWBBBWBBBWWWBBBNWWWBBW
    # 4BWNNBNBNNWWWNNWN
```

## 3.元件总数 （300分）  

小华有n个位置要放元件，元件的种类从0到2^k-1（1 <= n,k <= 1000000），形成一个元件环，相邻两个位置的元件不能XNOR为0，不然会爆炸（反异或）
0 XNOR 1 = 0
1 XNOR 1 = 1
问共有几种放置方式。%100000007。

通俗点讲就是相邻两个位置不能和为2^k-1。比如k=3，可以选0-7，那0旁边不能有7,1旁边不能有6……
001 （1） XNOR = 000 = 0
110 （6）

例：
输入3 1 输出2 （只有000和111两种）
输入2 2 输出12 （00,01,02,10,11,13,20,22,23,31,32,33）



