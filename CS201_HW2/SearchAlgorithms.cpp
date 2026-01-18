#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

void generateSortedArray(int* arr, int N) {
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % (10 * N + 1);
    }
    
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    int singleCount = 0;
    for (int i = 0; i < N; i++) {
        bool isDuplicate = false;
        for (int j = 0; j < singleCount; j++) {
            if (arr[j] == arr[i]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            arr[singleCount++] = arr[i];
        }
    }
    
    while (singleCount < N) {
        int newVal = rand() % (10 * N + 1);
        bool isDuplicate = false;
        for (int j = 0; j < singleCount; j++) {
            if (arr[j] == newVal) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            arr[singleCount++] = newVal;
        }
    }
    
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void findKClosestLinear(int* arr, int N, int target, int K, int* result) {
    int pos = 0;
    while (pos < N && arr[pos] < target) {
        pos++;
    }
    
    int left = pos - 1;
    int right = pos;
    int count = 0;
    
    while (count < K && (left >= 0 || right < N)) {
        if (left < 0) {
            result[count++] = arr[right++];
        } 
        else if (right >= N) {
            result[count++] = arr[left--];
        } 
        else {
            int diffLeft = target - arr[left];
            int diffRight = arr[right] - target;
            
            if (diffLeft <= diffRight) {
                result[count++] = arr[left--];
            } 
            else {
                result[count++] = arr[right++];
            }
        }
    }
}

int binarySearchPosition(int* arr, int N, int target) {
    int left = 0;
    int right = N - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } 
        else if (arr[mid] < target) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    
    return left; 
}

void findKClosestBinary(int* arr, int N, int target, int K, int* result) {
    int pos = binarySearchPosition(arr, N, target);
    
    int left = pos - 1;
    int right = pos;
    int count = 0;
    
    while (count < K && (left >= 0 || right < N)) {
        if (left < 0) {
            result[count++] = arr[right++];
        } 
        else if (right >= N) {
            result[count++] = arr[left--];
        } 
        else {
            int diffLeft = target - arr[left];
            int diffRight = arr[right] - target;
            
            if (diffLeft <= diffRight) {
                result[count++] = arr[left--];
            } 
            else {
                result[count++] = arr[right++];
            }
        }
    }
}

int jumpSearchPosition(int* arr, int N, int target) {
    int step = N;
    int prev = 0;
    
    while (prev < N && arr[prev] < target) {
        prev += step;
    }
    
    prev = prev - step > 0 ? prev - step : 0;
    while (prev < N && arr[prev] < target) {
        prev++;
    }
    
    return prev;
}

void findKClosestJump(int* arr, int N, int target, int K, int* result) {
    int pos = jumpSearchPosition(arr, N, target);
    
    int left = pos - 1;
    int right = pos;
    int count = 0;
    
    while (count < K && (left >= 0 || right < N)) {
        if (left < 0) {
            result[count++] = arr[right++];
        } 
        else if (right >= N) {
            result[count++] = arr[left--];
        } 
        else {
            int diffLeft = target - arr[left];
            int diffRight = arr[right] - target;
            
            if (diffLeft <= diffRight) {
                result[count++] = arr[left--];
            } 
            else {
                result[count++] = arr[right++];
            }
        }
    }
}

bool valueExists(int* arr, int N, int target) {
    for (int i = 0; i < N; i++) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

int main() {
    srand(time(0)); 
    
    int sizes[] = {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
    int numSizes = 13;
    
    int M = 1000; 
    
    cout << "N  Linear_K1   Linear_K2   Linear_K3   Linear_K4   ";
    cout << "Binary_K1  Binary_K2   Binary_K3   Binary_K4   ";
    cout << "Jump_K1    Jump_K2     Jump_K3     Jump_K4" << endl;
    
    for (int s = 0; s < numSizes; s++) {
        int N = sizes[s];
        
        int* arr = new int[N];
        generateSortedArray(arr, N);
        
        int target;
        do {
            target = rand() % (10 * N + 1);
        } while (valueExists(arr, N, target));
        
        int K_values[4];
        K_values[0] = 1;
        K_values[1] = N / 8;
        K_values[2] = N / 4;
        K_values[3] = N / 2;
        
        for (int i = 0; i < 4; i++) {
            if (K_values[i] < 1) K_values[i] = 1;
            if (K_values[i] > N) K_values[i] = N;
        }
        
        cout << N << "  ";
        
        //Linear Search
        for (int k_idx = 0; k_idx < 4; k_idx++) {
            int K = K_values[k_idx];
            int* result = new int[K];
            
            double duration;
            clock_t startTime = clock();
            
            for (int i = 0; i < M; i++) {
                findKClosestLinear(arr, N, target, K, result);
            }
            
            duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
            double avg_time = duration / M; 
            
            cout << avg_time << "   ";
            delete[] result;
        }
        
        //Binary Search
        for (int k_idx = 0; k_idx < 4; k_idx++) {
            int K = K_values[k_idx];
            int* result = new int[K];
            
            double duration;
            clock_t startTime = clock();
            
            for (int i = 0; i < M; i++) {
                findKClosestBinary(arr, N, target, K, result);
            }
            
            duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
            double avg_time = duration / M;
            
            cout << avg_time << "   ";
            delete[] result;
        }
        
        //Jump Search
        for (int k_idx = 0; k_idx < 4; k_idx++) {
            int K = K_values[k_idx];
            int* result = new int[K];
            
            double duration;
            clock_t startTime = clock();
            
            for (int i = 0; i < M; i++) {
                findKClosestJump(arr, N, target, K, result);
            }
            
            duration = 1000 * double(clock() - startTime) / CLOCKS_PER_SEC;
            double avg_time = duration / M;
            
            cout << avg_time << "   ";
            delete[] result;
        }
        
        cout << endl;
        delete[] arr;
    }
    
    return 0;
}