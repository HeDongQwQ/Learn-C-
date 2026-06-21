#include <iostream>
#include <cuda_runtime.h>

__global__ void square(int *data)
{
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < 1000000)
    {
        data[idx] = idx * idx;
    }
}

int main()
{
    const int N = 1000000;
    const int SIZE = N * sizeof(int);

    int *h_data = new int[N];
    int *d_data;

    cudaMalloc(&d_data, SIZE);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    square<<<(N + 255) / 256, 256>>>(d_data);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms = 0;
    cudaEventElapsedTime(&ms, start, stop);

    cudaMemcpy(h_data, d_data, SIZE, cudaMemcpyDeviceToHost);

    std::cout << "GPU finished!\n";
    std::cout << "Time: " << ms << " ms\n\n";

    std::cout << "First 10 results:\n";

    for (int i = 0; i < 10; i++)
    {
        std::cout << i << "^2 = " << h_data[i] << std::endl;
    }

    cudaFree(d_data);
    delete[] h_data;

    return 0;
}