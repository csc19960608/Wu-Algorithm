#include<vector>
#include<multiset>
#include<unordered_map>
using namespace std;

//从字符串寻找子字符串的加强版
//最笨的方法，穷举words可能排列，然后一个个查找
//超时！！！
class Solution1{ 
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int>result;
        if(words.empty()){
            return result;
        }
        int wordSize=words[0].size();
        multiset<string>wordSet(words.begin(),words.end());
        multiset<string>temp;
        for(int i=0;i<s.size();i++){
            if(i+words.size()*wordSize>s.size())
                break;
            if(wordSet.find(s.substr(i,wordSize))!=wordSet.end()){
                temp.insert(s.substr(i,wordSize));
                int j=1;
                while(j<words.size()){
                    if(wordSet.find(s.substr(i+j*wordSize,wordSize))!=wordSet.end()){
                        temp.insert(s.substr(i+j*wordSize,wordSize));
                        j++;
                    }
                    else break;
                }
                if(j==words.size() && mismatch(wordSet.begin(),wordSet.end(),temp.begin()).first==wordSet.end())
                    result.push_back(i);
                temp.clear();
            }
        }
        return result;
    }
};

/*
这道题还有一种O(n)时间复杂度的解法，设计思路非常巧妙，但是感觉很难想出来。
这种方法不再是一个字符一个字符的遍历，而是一个词一个词的遍历，比如根据题目中的例子，字符串s的长度n为18，words数组中有两个单词(cnt=2)，每个单词的长度len均为3，那么遍历的顺序为0，3，6，8，12，15，然后偏移一个字符1，4，7，9，13，16，然后再偏移一个字符2，5，8，10，14，17，这样就可以把所有情况都遍历到.
我们还是先用一个哈希表m1来记录words里的所有词，然后我们从0开始遍历，用left来记录左边界的位置，count表示当前已经匹配的单词的个数。然后我们一个单词一个单词的遍历，如果当前遍历的到的单词t在m1中存在，那么我们将其加入另一个哈希表m2中，如果在m2中个数小于等于m1中的个数，那么我们count自增1，如果大于了，那么需要做一些处理，比如下面这种情况, s = barfoofoo, words = {bar, foo, abc}, 我们给words中新加了一个abc，目的是为了遍历到barfoo不会停止，那么当遍历到第二foo的时候, m2[foo]=2, 而此时m1[foo]=1，这是后已经不连续了，所以我们要移动左边界left的位置，我们先把第一个词t1=bar取出来，然后将m2[t1]自减1，如果此时m2[t1]<m1[t1]了，说明一个匹配没了，那么对应的count也要自减1，然后左边界加上个len，这样就可以了。如果某个时刻count和cnt相等了，说明我们成功匹配了一个位置，那么将当前左边界left存入结果res中，此时去掉最左边的一个词，同时count自减1，左边界右移len，继续匹配。如果我们匹配到一个不在m1中的词，那么说明跟前面已经断开了，我们重置m2，count为0，左边界left移到j+len
*/
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.size()==0) {
            return result;
        }
        
        unordered_map<string, int> hash;
        for (int i=0; i < words.size(); i++) {
            if (hash.find(words[i]) == hash.end()) {
                hash[words[i]]=1;
            } else {
                hash[words[i]]++;
            }
        }
        
        int wSize = words[0].length();
    for (int start=0; start < wSize; start++) {
            int wCount=0;
            unordered_map<string, int> slidingWindow;
            for (int i=start; i+wSize<=s.length(); i+=wSize) {
                string word = s.substr(i, wSize);
                if (hash.find(word) == hash.end()) {
                    slidingWindow.clear();
                    wCount = 0;
                } else {
                    wCount++;
                    if (slidingWindow.find(word) == slidingWindow.end()) {
                        slidingWindow[word]=1;
                    } else {
                        slidingWindow[word]++;
                    }
                    while (hash[word] < slidingWindow[word]) {
                        string removedWord = s.substr(i-(wCount-1)*wSize, wSize);
                        slidingWindow[removedWord]--;
                        wCount--;
                    }
                }
                
                if (wCount == words.size()) {
                    result.push_back(i-(wCount-1)*wSize);
                }
            }
        }
        return result;
    }
};