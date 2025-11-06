# 資料結構 HW2
---
## Contents
- [Test](#Test)
    - [Binary Search Tree](#BST)
    - [AVL Tree](#AVLTree)
    - [Treap](#Treap)
    - [Skip List](#SkipList)

- [Experiment](#Experiment)
    - [Insertion Time](#InsertionTime)
    - [Average Search Time](#AverageSearchTime)
    - [Average Height](#AverageHeight)

- [Implementation Explanation](#IE)

- [Thoughts](#Thoughts)

## Test<a id=Test></a>
* ### Binary Search Tree<a id=BST></a>
```
BST Test :
Insert data : (3, 100)、(2, 60)、(1, 70)、(5, 40)、(4, 70)
(      3, 100.00) (      5,  40.00) 
                                    (      4,  70.00) 
                  (      2,  60.00) 
                                    (      1,  70.00) 
3
Id 0 average = -1
Id 1 average = 70
Id 2 average = 60
Id 3 average = 100
Id 4 average = 70
Id 5 average = 40
```
print()輸出說明:樹的根節點在左側，葉節點在右側；右子樹在上，左子樹在下，以下樹結構都是用相同的輸出邏輯。<br>
可以確認所有的左子樹中所有節點都小於父節點，右子樹中所有節點大於父節點，並且分數正確。<br>
* ### AVL Tree<a id=AVLTree></a>
```
AVLTree Test:
Insert data: (1, 100)、(2, 60)、(3, 70)、(4, 40)、(5, 70)
(      2,  60.00) (      4,  40.00) (      5,  70.00) 
                                    (      3,  70.00) 
                  (      1, 100.00) 
3
Id 0 average = -1
Id 1 average = 100
Id 2 average = 60
Id 3 average = 70
Id 4 average = 40
Id 5 average = 70
```
插入3、5時都有正確平衡，並且也滿足所有的左子樹中所有節點都小於父節點，右子樹中所有節點大於父節點，並且分數正確。<br>
* ### Treap<a id=Treap></a>
```
Treap Test:
Insert data: (3,100)[0.9]、(2,60)[0.5]、(1,70)[0.3]、(5,60)[0.2]、(4,80)[0.1]
(      4,  80.00)[0.1000] (      5,  60.00)[0.2000] 
                          (      1,  70.00)[0.3000] (      2,  60.00)[0.5000] (      3, 100.00)[0.9000] 
4
Id 0 average = -1
Id 1 average = 70
Id 2 average = 60
Id 3 average = 100
Id 4 average = 80
Id 5 average = 60
```
priority是[]內的數字。<br>
父節點的priority小於子節點的priority，且滿足所有的左子樹中所有節點都小於父節點，右子樹中所有節點大於父節點，並且分數正確。<br>
* ### Skip List<A id=SkipList></a>
```
SkipList Test:
Insert data: (1, 100)[HHT]、(2,60)[T]、(3, 70)[HT]、(4,80)[HHHT]、(5,60)[T]、(6,80)[T]、(7,90)[HHT]
                                                      (      4,  80.00)
(      1, 100.00)                                     (      4,  80.00)                                     (      7,  90.00)       
(      1, 100.00)                   (      3,  70.00) (      4,  80.00)                                     (      7,  90.00)       
(      1, 100.00) (      2,  60.00) (      3,  70.00) (      4,  80.00) (      5,  60.00) (      6,  80.00) (      7,  90.00)       
4
Id 0 average = -1
Id 1 average = 100
Id 2 average = 60
Id 3 average = 70
Id 4 average = 80
Id 5 average = 60
```
左邊是頭，右邊是尾，省略開頭的輔助節點。<br>
id排序、結構、分數都正確。<br>
## Experiment<a id=Experiment></a>
* ### Environment
    - CPU: 12th Gen Intel(R) Core(TM) i7-12700 (2.10 GHz)
    - RAM: 24GB
    - OS: Windows 11 家用版 25H2 (Build 26200.6899)
    - Compiler: Visual Studio 2022 (MSVC)
  
* ### Result
    1. ##### Insertion time<a id=InsertionTime></a>
    ![Insertion Time](https://github.com/antyee87/DataStructureHW2/blob/main/experiment1.png?raw=true)
    <br>
    每個結構插入的時間複雜度都是O(log n)，雖然Binary Search Tree(以下簡稱BST)的髙度會略髙於AVL Tree，與Treap持平，但由於AVL Tree跟Treap需要靠旋轉來維持性質，所以BST速度最快，AVL Tree與Treap速度持平。不過Skip List慢其它結構5倍左右，原本以為只會慢2倍左右，大概是因為cache miss之類的CPU機制，但我也沒什麼優化方法。<br>

    2. ##### Average Search Time<a id=AverageSearchTime></a>
    ![Average Search Time](https://github.com/antyee87/DataStructureHW2/blob/main/experiment2.png?raw=true)
    <br>
    每個結構搜尋的時間複雜度都是O(log n)，Skip List受製於機制，通過的節點數量大概會是BST的兩倍，平均橫向通過log n個節點，縱向也通過log n個節點。奇妙的是明明BST跟Treap的髙度差不多，用的也是同樣的搜尋程式碼，但搜尋速度卻是Treap稍慢，我認為可能是因為Treap更經常旋轉，原本短時間內分配的的記憶體位址會更相近，所以BST的父節點跟子節點的記憶體位址更近，但旋轉會打亂原本的節點分布，導致Treap更容易cache miss。然後AVL Tree是平均髙度最低的樹，也不出意外的搜尋速度最快。有些數據沒那麼平滑，不知道是不是有什麼其他程式造成的外部影響。<br>

    3. ##### Average Height<a id=AverageHeight></a>
    ![AverageHeight](https://github.com/antyee87/DataStructureHW2/blob/main/experiment3.png?raw=true)
    <br>
    確認在隨機數據的情況下，BST跟Treap的表現相同，然後髙度增長速度比其它結構快一點，還注意到Skip List在擲銅板正面機率為0.75的情況下，高度居然跟BST、Treap差不多，不知是巧合還是有什麼理由。<br>
## Implementation Explanation<a id=IE></a>
 1. ##### 如何讓id有多個score?
    建立一個資料結構，儲存id跟scores的動態陣列，每次insert score時，將score放入scores，不過id並非必要，只是這樣感覺更好。<br>
 2. ##### AVL tree在rebalance時如何找到median?
    根據平衡因子(balance factor)窮舉四個可能。
    ```
    node:待平衡子樹的根節點
    if (abs(node balance factor)>bound):
        if (node balance factor > 0):
            if (node's left child balance factor > 0):
                median = LL
            else:
                median = LR
        else:
            if (node's right child balance factor < 0):
                median = RR
            else:
                median = RL
    ```
    <br>
 3. ##### 如何實作向上旋轉?
    根據待向上旋轉節點是父節點的左子節點還是右子節點決定旋轉邏輯，並且旋轉完後該節點會成為子樹的根節點。