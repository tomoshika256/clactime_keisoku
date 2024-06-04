#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
int main(void) {
    long init_size = 1e7;

    for (int data_dankai = 1; data_dankai <= 10; data_dankai++) {
        long size = init_size * data_dankai;
        std::vector<long> a(size);
        for (long i = 0; i < size; i++) {
            a[i] = i;
        }
        long zikken_kaisu = 1e7;
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
        // シャッフル
        std::shuffle(a.begin(), a.end(), engine);

        //ハッシュのデータ格納
        long m = 1.5 * size;
        std::vector<long> H(m);

        for (long i = 0; i < size; i++) {
            long k = a[i] % m;
            while (H[k]) {
                k = (k + 1) % m;
            }

            H[k] = a[i];
        }

        clock_t start = clock();    // スタート時間
        for (long zikkou_cnt = 0; zikkou_cnt < zikken_kaisu; zikkou_cnt++) {

            /*
            データセットの中身の確認
            for (long i = 0; i < size; i++) {
                cout << a[i] << endl;
            }
            */

            long look_for = engine() % size;

            /*
            //線形探索の開始
            long i = 0;
            while (i < size) {
                if (look_for == a[i])break;
                else { i++; }
            }
            */


            //二分探索
            /*
            long left = 0, right = size - 1, mid = (left + right) / 2;
            while (left < right) {
                if (a[mid] == look_for) { break; }
                else if (a[mid] < look_for)left = mid + 1;
                else { right = mid - 1; }
                mid = (left + right) / 2;
            }
            */

            //ハッシュ法
            long k = look_for % m;
            while (H[k]) {
                if (H[k] == look_for) 
                    break;
                k = (k + 1) % m;
            }
        }
        clock_t end = clock();     // 終了時間
        double zikkou_zikan = (double)(end - start); // 経過時間を計算
        //std::cout << "データサイズ=" << size << "のときの" << "線形探索の処理にかかった時間: " << zikkou_zikan << "[ms]" << std::endl;
        //std::cout << "データサイズ=" << size << "のときの" << "二分探索の処理にかかった時間: " << zikkou_zikan << "[ms]" << std::endl;
        std::cout << "データサイズ=" << size << "のときの" << "ハッシュ法の処理にかかった時間: " << zikkou_zikan << "[ms]" << std::endl;
    }
}
