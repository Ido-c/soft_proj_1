# take input and save it i vars

k = 0
n = 0
d = 0
max_iter = 0

vectors = [[] for i in range(n)]
centroids = [[] for i in range(k)]
clustrers = [[] for i in range(n)]

#


""":returns the index of the cluset centroid """


def find_closest_cluster(x, centroids, ):
    distances = []
    for param in centroids:
        distances.append(getDistance(x, param))
    min_distence = distances[0]
    min_index = 0
    for i in range(len(distances)):
        if distances[i] < min_distence:
            min_index = i
            min_distence = distances[i]
    return min_index


def getDistance(vec1, vec2):
    sum = 0
    for (num1, num2) in (vec1, vec2):
        sum += pow(num1 - num2, 2)
    return sum


def update_centroid(clusterVec, centroidVec, allVecs):
    vector_of_sums = [0 for i in range(len(centroidVec))]
    flag =False
    for elem in clusterVec:
        for (sum, num) in (vector_of_sums,elem):
            sum+=num
