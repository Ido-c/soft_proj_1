# take input and save it i vars
import argparse



def main(k, n, d, max_iter):


    vectors = []
    while True:
        try:
            temp_list = input().split(",")
            vectors.append([])
            for num in temp_list:
                vectors[-1].append(float(num))
        except EOFError:
            break

    centroids = [vectors[i].copy() for i in range(k)]
    clusters = [[] for i in range(k)]
    change = False  # tell us if clusters change
    for num_of_tries in range(max_iter):
        # put vectors in clusters
        for vec in vectors:
            clusters[find_closest_cluster(vec,centroids)].append(vec)
            # recalculate cent
        for i in range(len(clusters)):
            if update_centroid(clusters[i], centroids[i]):
                change = True
        if not change:
            break
        clusters = [[] for i in range(k)]
    # printing the centroid results
    for cent in centroids:
        for i in range(len(cent)):
            print("{:.2f}".format(cent[i]),end= "")
            if i != (len(cent) - 1):
                print(",",end="")
        print("")


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
    dis = 0
    for (num1, num2) in zip(vec1, vec2):
        dis += pow(num1 - num2, 2)
    return dis


def update_centroid(clusterVec, centroidVec):
    vector_of_sums = [0 for i in range(len(centroidVec))]
    flag = False
    for elem in clusterVec:
        for i in range(len(vector_of_sums)):
            vector_of_sums[i] += elem[i]

    for i in range(len(centroidVec)):
        new_val = vector_of_sums[i] / len(clusterVec)
        if (new_val != centroidVec[i]):
            flag = True
        centroidVec[i] = new_val
    return flag


parser = argparse.ArgumentParser()
parser.add_argument("k", type=int)
parser.add_argument("n", type=int)
parser.add_argument("d", type=int)
parser.add_argument("max_iter", type=int)
args = parser.parse_args()

main(args.k,args.n,args.d,args.max_iter)