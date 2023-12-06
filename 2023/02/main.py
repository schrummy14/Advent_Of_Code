#!/usr/bin/env python3

MAX_BALLS = {
    "red": 12,
    "green": 13,
    "blue": 14
}

def getCalibrationNumberPart1(line:str) -> int:
    gameNumber = line.strip().split(':')[0].strip().split(' ')[1]
    games = line.strip().split(':')[1].strip().split(';')
    for game in games:
        balls = game.strip().split(',')
        for ball in balls:
            numberAndColor = ball.strip().split(' ')
            numberOfBalls = int(numberAndColor[0].strip())
            colorOfBalls = numberAndColor[1].strip()
            if numberOfBalls > MAX_BALLS.get(colorOfBalls,0):
                return 0
    return int(gameNumber)

def getCalibrationNumberPart2(line:str) -> int:
    minNumberBalls = {
        'red':0,
        'green':0,
        'blue':0
    }
    games = line.strip().split(':')[1].strip().split(';')
    for game in games:
        balls = game.strip().split(',')
        for ball in balls:
            numberAndColor = ball.strip().split(' ')
            numberOfBalls = int(numberAndColor[0].strip())
            colorOfBalls = numberAndColor[1].strip()
            if colorOfBalls not in minNumberBalls:
                print('hi')
                exit()
            if numberOfBalls > minNumberBalls[colorOfBalls]:
                minNumberBalls[colorOfBalls] = numberOfBalls
    powerNumber = 1
    for mb in minNumberBalls:
        powerNumber *= minNumberBalls[mb]
    return powerNumber

def main():
    totalCalibration = 0
    with open('input.dat','r') as f:
        for l in f:
            line = l.strip()
            if not line:
                continue
            totalCalibration += getCalibrationNumberPart2(line)
    print(totalCalibration)

if __name__ == "__main__":
    main()
