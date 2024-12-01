# LBYARCH_x86-64 Interface Programming Project  
### By Shaimma Salic and Trisha Valladolid (S14)  

---

## **Overview**  
This project implements a kernel to transform a two-dimensional array of grayscale pixel values (stored as doubles) into scaled integer values. Two implementations are provided: one in C and another in x86-64 assembly using SIMD instructions. The program demonstrates efficient conversion of grayscale image representations from floating-point to integer-based formats, comparing performance between C and assembly language.

---

## **Structure and Workflow**  

### **C Implementation (`main.c`)**  
#### **Purpose**  
- Converts each grayscale value in a 2D array to an integer by multiplying it with a scaling factor (255.0).  
- Manages memory allocation for both input and output arrays.  
- Reads array dimensions and pixel values directly from user input.  
- Displays the processed output.  
- Executes the execution time test multiple times (e.g., 30 iterations) to calculate average runtime.  

---

### **x86-64 Assembly Implementation (`asmfunc.asm`)**  
#### **Purpose**  
- Converts each grayscale value in a 2D array to an integer in optimized assembly code.  
- Utilizes SIMD instructions to accelerate floating-point calculations.  
- Processes rows sequentially to enhance memory access efficiency.  
- Works with the C program for seamless benchmarking and result validation.  

---

## **How to Run**  

1. **Download Zip File**
2. **Extract File**
3. **Adjust properties**
4. **Build asm file**
5. **Run**

---

## **How to Run**  
