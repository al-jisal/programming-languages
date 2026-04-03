function binary_search(nums: Array<number>, target: number): boolean {
    let left = 0 ;
    let right = nums.length - 1;
    
    while (left <= right){
        let mid = Math.floor((left + right) / 2);
        if (nums[mid] < target)
            left = mid + 1;
        else if (nums[mid] > target)
            right = mid - 1;
        else
            return true;
    }

    return false;
}

let pay = [2, 7, 13, 17, 18, 25, 40];

console.log(binary_search(pay, 17));