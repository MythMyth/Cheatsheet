#include<bits/stdc++.h>

struct SegmentTree {
        int n;
        vector<int> tree;
        vector<int> lazy;

        int getMid(int start, int end) {
            return start + (end - start)/2;
        }

        SegmentTree(int maxCoor) {
            n = maxCoor;
            int height = (int)(ceil(log2(n)));
            int max_size = 2*(int)pow(2, height) - 1;
            tree.resize(max_size, 0);
            lazy.resize(max_size , 0);
        }

        void updateRangeUtil(int start, int end, int rangeStart, int rangeEnd, int segNode, int val) {
            if(lazy[segNode] != 0) {
                tree[segNode] = lazy[segNode];
                if(rangeStart != rangeEnd) {
                    lazy[segNode * 2 + 1] = lazy[segNode];
                    lazy[segNode * 2 + 2] = lazy[segNode];
                }
                lazy[segNode] = 0;
            }

            if(rangeStart > end || rangeEnd < start) {
                return;
            }

            if(start <= rangeStart && rangeEnd <= end) {
                tree[segNode] = max(val, tree[segNode]);
                if(rangeStart != rangeEnd) {
                    lazy[segNode*2 + 1] = max(lazy[segNode*2 + 1], val);
                    lazy[segNode*2 + 2] = max(lazy[segNode*2 + 2], val);
                }
                return;
            }
            int mid = getMid(rangeStart, rangeEnd);
            updateRangeUtil(start, end, rangeStart, mid, segNode * 2 + 1, val);
            updateRangeUtil(start, end, mid+1, rangeEnd, segNode * 2 + 2, val);

            tree[segNode] = max(tree[segNode], max(tree[segNode * 2 + 1], tree[segNode * 2 + 2]));
        }

        void updateRange(int start, int end, int val) {
            updateRangeUtil(start, end, 0, n-1, 0, val);
        }

        int getRangeUtil(int start, int end , int rangeStart, int rangeEnd, int segNode) {

            if(lazy[segNode] != 0) {
                tree[segNode] = lazy[segNode];
                if(rangeStart != rangeEnd) {
                    lazy[segNode * 2 + 1] = lazy[segNode];
                    lazy[segNode * 2 + 2] = lazy[segNode];
                }
                lazy[segNode] = 0;
            }

            if(rangeEnd < start || end < rangeStart) return 0;
            if(start <= rangeStart && rangeEnd <= end) return tree[segNode];
            int mid = getMid(rangeStart, rangeEnd);
            return max(getRangeUtil(start, end, rangeStart, mid, segNode*2 + 1),getRangeUtil(start, end, mid+1, rangeEnd, segNode*2 + 2));
        }

        int getRange(int start, int end) {
            return getRangeUtil(start, end, 0, n - 1, 0);
        }

    };
