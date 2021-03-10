class Trie // 字典树模板
{
private:
    bool is_string = false; // 判断是不是单词结尾
    Trie *next[26] = {nullptr}; // 26个小写字母
public:
    Trie( ) { }
    // 一般而言，字典树的基本结构主要实现两种功能：1.插入；2.查找。
    void insert(const string& word) // 插入单词
    {
        Trie *root = this;
        for(const auto& w : word){
            if (root->next[w - 'a'] == nullptr) root->next[w - 'a'] = new Trie();
            root = root->next[w - 'a'];
        }
        root->is_string = true;
    }

    bool search(const string& word) // 查找单词
    {
        Trie* root = this;
        for(const auto& w : word){
            if (root->next[w - 'a'] == nullptr) return false;
            root = root->next[w - 'a'];
        }
        return root->is_string;
    }

    bool startsWith(string prefix) // 查找前缀
    {
        Trie* root = this;
        for (const auto& p : prefix){
            if (root->next[p - 'a'] == nullptr) return false;
            root = root->next[p - 'a'];
        }
        return true;
    }
};

// https://leetcode-cn.com/problems/maximum-xor-of-two-numbers-in-an-array/solution/ctriemo-ban-ti-song-ban-zi-by-xiaoneng-tegw/
