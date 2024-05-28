def twoSum(nums, target):
    """
    :param nums: List[int]
    :param target: int
    :return: List[int]
    """
    for i in range(len(nums)):
        for j in range(i + 1, len(nums)):
            if nums[i] + nums[j] == target:
                return [i, j]
    return []

def main():
    nums = [3, 2, 3]
    target = 6
    indexes = twoSum(nums, target)
    if indexes:
        print(indexes[0], indexes[1])
    else:
        print("Not found")

if __name__ == "__main__":
    main()