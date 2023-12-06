#!/usr/bin/env python3

import tqdm
import multiprocessing as mp
import time

class Data:
    def __init__(self):
        self.seeds = []
        self.seed_to_soil = []
        self.soil_to_fertilizer = []
        self.fertilizer_to_water = []
        self.water_to_light = []
        self.light_to_temperature = []
        self.temperature_to_humidity = []
        self.humidity_to_location = []

    def getLocationFromSeed(self, seed:int) -> int:
        soil = self.getSoilFromSeed(seed)
        fert = self.getFertilizerFromSoil(soil)
        watr = self.getWaterFromFertilizer(fert)
        liht = self.getLightFromWater(watr)
        temp = self.getTemperatureFromLight(liht)
        humd = self.getHumidityFromTemperature(temp)
        loct = self.getLocationFromHumidity(humd)

        # print(f"{seed} -> {soil} -> {fert} -> {watr} -> {liht} -> {temp} -> {humd} -> {loct}")
        return loct

    def getSoilFromSeed(self, seed:int) -> int:
        return self.__get_b_from_a(seed, self.seed_to_soil)

    def getFertilizerFromSoil(self, soil:int) -> int:
        return self.__get_b_from_a(soil, self.soil_to_fertilizer)

    def getWaterFromFertilizer(self, fert:int) -> int:
        return self.__get_b_from_a(fert, self.fertilizer_to_water)

    def getLightFromWater(self, watr):
        return self.__get_b_from_a(watr, self.water_to_light)

    def getTemperatureFromLight(self, light):
        return self.__get_b_from_a(light, self.light_to_temperature)

    def getHumidityFromTemperature(self, temp):
        return self.__get_b_from_a(temp, self.temperature_to_humidity)

    def getLocationFromHumidity(self, humidity):
        return self.__get_b_from_a(humidity, self.humidity_to_location)


    def __get_b_from_a(self, a, curList) -> int:
        for entry in curList:
            dif = a - entry[1]
            if 0 <= dif < entry[-1]:
                return entry[0] + dif
        return a

    def print(self):
        print(f"seeds: {self.seeds}")
        print(f"seeds to soil: {self.seed_to_soil}")
        print(f"soil to fertilizer: {self.soil_to_fertilizer}")
        print(f"fertilizer to water: {self.fertilizer_to_water}")
        print(f"water to light: {self.water_to_light}")
        print(f"light to temperature: {self.light_to_temperature}")
        print(f"temperature to humidity: {self.temperature_to_humidity}")
        print(f"humidity to location: {self.humidity_to_location}")

def getData(filename:str) -> Data:
    data = Data()
    with open(filename, 'r') as f:
        data.seeds = [int(s) for s in f.readline().strip().split(':')[-1].strip().split()]
        f.readline()
        f.readline()
        line = f.readline().strip()
        while line:
            data.seed_to_soil.append([int(s) for s in line.split()])
            line = f.readline().strip()

        f.readline()
        line = f.readline().strip()
        while line:
            data.soil_to_fertilizer.append([int(s) for s in line.split()])
            line = f.readline().strip()

        f.readline()
        line = f.readline().strip()
        while line:
            data.fertilizer_to_water.append([int(s) for s in line.split()])
            line = f.readline().strip()

        f.readline()
        line = f.readline().strip()
        while line:
            data.water_to_light.append([int(s) for s in line.split()])
            line = f.readline().strip()

        f.readline()
        line = f.readline().strip()
        while line:
            data.light_to_temperature.append([int(s) for s in line.split()])
            line = f.readline().strip()

        f.readline()
        line = f.readline().strip()
        while line:
            data.temperature_to_humidity.append([int(s) for s in line.split()])
            line = f.readline().strip()

        f.readline()
        line = f.readline().strip()
        while line:
            data.humidity_to_location.append([int(s) for s in line.split()])
            line = f.readline().strip()

    return data

def doPart_1(data:Data):
    minLocation = None
    for seed in data.seeds:
        location = data.getLocationFromSeed(seed)
        if minLocation is None or location < minLocation:
            minLocation = location
    return minLocation

def getAllSeeds(seedRangePairs):
    # seeds = list()
    k = 0
    while k < len(seedRangePairs):
        start = seedRangePairs[k]
        length = seedRangePairs[k+1]
        for m in range(length):
            yield start+m
            # seeds.append(start+m)
        k+=2
    # return seeds

def getTotalInstances(seedRangePairs):
    k = 1
    tot = 0
    while k < len(seedRangePairs):
        tot += seedRangePairs[k]
        k +=2
    return tot

def doPart_2(data:Data):
    minLocation = None
    num_cpus = mp.cpu_count()//2
    pool = mp.Pool(num_cpus)

    # Need to batch 1 million seeds at a time
    batch_size = 1000000

    # k = 12
    k = 0
    startOfProgram = time.time()
    timeStart = time.time()
    while k < len(data.seeds):
        start = k
        stop = k+2
        seedStart,seedRange = data.seeds[start:stop]
        print(seedStart, seedRange)
        batchSeeds = []
        for j in range(seedRange//batch_size):
            batchSeeds.append(seedStart + j*batch_size)
            batchSeeds.append(batch_size)
        batchSeeds.append(seedStart + seedRange//batch_size * batch_size)
        batchSeeds.append(seedStart + seedRange - (seedStart + seedRange//batch_size * batch_size))

        for j in tqdm.tqdm(range(0,len(batchSeeds),2)):
            batchStart = j
            batchStop = j+2
            seeds = getAllSeeds(batchSeeds[batchStart:batchStop])
            results = pool.map(data.getLocationFromSeed, seeds)
            for r in results:
                if minLocation is None or r < minLocation:
                    minLocation = r
        k+=2
        perDone = 100 * k / len(data.seeds)
        CPU_TIME = time.time()-startOfProgram
        print(f"{perDone:0.2f}% - CPU: {CPU_TIME:0.2f} - minLocation: {minLocation}")

        # seeds = getAllSeeds(data.seeds[start:stop])
        # results = pool.map(data.getLocationFromSeed, seeds)
        # for r in results:
        #     if minLocation is None or r < minLocation:
        #         minLocation = r
        # k+=2
        # newTime = time.time()
        # eps = (newTime - timeStart)
        # timeStart = newTime
        # eta = eps/2 * len(data.seeds) - eps
        # perDone = 100 * k / len(data.seeds)
        # CPU_TIME = time.time()-startOfProgram
        # print(f"{perDone:0.2f}% - ETA: {eta:0.2f} seconds - CPU: {CPU_TIME:0.2f} - minLocation: {minLocation}")

    return minLocation

def doPart_2b(data:Data):
    for k in range(0,len(data.seeds),2):
        seed_0, seed_1 = data.seeds[k],data.seeds[k]+data.seeds[k+1]-1
        for soil in data.seed_to_soil:
            soil_0 = max(seed_0,soil[1]+soil[2])
        print(seed_0, seed_1)


def main():
    # data = getData('example.dat')
    data = getData('input.dat')
    # answer = doPart_1(data)
    answer = doPart_2(data)
    # answer = doPart_2b(data)
    print("answer:", answer)

if __name__ == "__main__":
    main()
