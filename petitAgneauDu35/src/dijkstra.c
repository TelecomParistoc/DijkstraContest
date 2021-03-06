#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dijkstra.h"
#include "utils.h"
#include "path.h"

// The margin to leave between the robots and the obstacles
static int margin;

// The map describing the table
static Node* map[WIDTH * LENGTH];

static Obstacle obstacle;

static int xMax, yMax, radius, xStart, yStart, xStop, yStop, distance_map;

static int xPos, yPos, halfWidth, halfHeight, angle;

int main(int argc, char* argv[]) {
	if (argc > 2 || (argc == 2 && strcmp(argv[1], "map") != 0)) {
		printf("Syntax : %s [map]\n", argv[0]);
		return 1;
	}
	if(argc == 2 && strcmp(argv[1], "map") == 0)
		distance_map = 1;
	else
		distance_map = 0;
	int ret = 0;
	ret += scanf("%i[ \n]", &xMax); // No more used
	ret += scanf("%i[ \n]", &yMax); // No more used
	ret += scanf("%i[ \n]", &radius);
	ret += scanf("%i[ \n]", &xStart);
	ret += scanf("%i[ \n]", &yStart);
	ret += scanf("%i[ \n]", &xStop);
	ret += scanf("%i[ \n]", &yStop);

	if (ret != 7)
		return -1; // Error when reading input data

	//Recuperation des coordonnees des obstacles

	//Initialization of the map
	for (int i = 0; i < xMax; i++) {
		for (int j = 0; j < yMax; j++) {
			map[i * yMax + j] = (Node*)malloc(sizeof(Node));
			map[i * yMax + j]->accessible = 1;
			map[i * yMax + j]->A = 0;
			map[i * yMax + j]->distance = INT_MAX;
			map[i * yMax + j]->point.x = i;
			map[i * yMax + j]->point.y = j;
			map[i * yMax + j]->pere = map[i * yMax + j];
		}
	}

	while(scanf("%i[ \n]", &xPos) != EOF) {
		if (feof(stdin))
			break;
		//Fill the data about the obstacle
		ret = 0;
		ret += scanf("%i[ \n]", &halfWidth);
		ret += scanf("%i[ \n]", &yPos);
		ret += scanf("%i[ \n]", &halfHeight);
		ret += scanf("%i", &angle);
		if (ret != 4)
			break;
		init_obstacle(&obstacle, xPos, yPos, halfWidth, halfHeight, angle, radius);
		set_obstacle(map, &obstacle, xMax, yMax, radius);
	}

	//Initialisation du pivot initial (point de depart)
	map[xStart * yMax + yStart]->A = 1;
	map[xStart * yMax + yStart]->distance = 0;
	Node* pivot = map[xStart * yMax + yStart];

	int x, y, cost;
	Node* cur;
	margin = radius + MARGIN;

	//Beginning of the algorithm
	for (int i = 0; i < xMax * yMax - 1; i++) {
		//Pour l'ensemble des voisins de pivot
		for(int j = -1; j <= 1; j++) {
			for (int k = -1; k <= 1; k++) {
				//Sans compter le pivot evidemment
				if (j != 0 || k != 0) {
					//printf("i = %i, j = %i, k = %i\n", i, j, k);
					x = pivot->point.x + j;
					y = pivot->point.y + k;
					if (map[x * yMax + y]->accessible && map[x * yMax + y]->A == 0) {
						cur = map[x * yMax + y];
						if(j == 0 || k == 0)
							cost = 2;
						else
							cost = 3; //Higher cost for diagonals
						if(pivot->distance + cost < cur->distance) {
							cur->distance = pivot->distance + cost;
							cur->pere = pivot;
						}
					}
				}
			}
		}
		pivot = nextPivot(map, xMax, yMax, margin, pivot->distance);
		pivot->A = 1;
		//On s'arrete des qu'on a atteint la destination
		if(pivot->point.x == xStop && pivot->point.y == yStop) {
			break;
		}
	}

	//Recuperation du nombre de noeuds sur le chemin
	x = xStop;
	y = yStop;
	Node* pere;
	int nb = 1;
	while(x != xStart || y != yStart) {
		pere = map[x * yMax + y]->pere;
		x = pere->point.x;
		y = pere->point.y;
		nb++;
	}
	//Recuperation des coordonnees successives des noeuds sur le chemin
	x = xStop;
	y = yStop;
	int cnt = nb;
	int path[2 * nb];
	while (x != xStart || y != yStart) {
		path[2 * cnt - 1] = y;
		path[2 * cnt - 2] = x;
		pere = map[x * yMax + y]->pere;
		x = pere->point.x;
		y = pere->point.y;
		cnt--;
	}
	path[0] = xStart;
	path[1] = yStart;

	//Affichage du chemin
	/*for (int i = 0; i < 2* nb; i++) {
		printf("%i ", path[i]);
	}

	printf("\n\n");*/
	concat_path(path, nb);

	if (distance_map) {
		printf("\n\n");
		printCost(map, xMax, yMax);
	}
	return 0;
}

Node* nextPivot(Node* map[], int xMax, int yMax, int margin, int distMin) {
	//return the next pivot
	Node* pivot = (Node*)malloc(sizeof(Node));
	//Keep track of the address of the space allocated to free it before returning
	Node* p = pivot;
	pivot->distance = INT_MAX;
	for (int x = margin; x < xMax - margin; x++) {
		for (int y = margin; y < yMax - margin; y++) {
			if(map[x * yMax + y]->accessible == 1 && map[x * yMax + y]->A == 0 && map[x * yMax + y]->distance < pivot->distance) {
				pivot = map[x * yMax + y];
				/*
				La distance jusqu'au prochain pivot est au moins aussi grande que celle jusqu'à l'ancien pivot.
				*/
				if (pivot->distance == distMin) {
					free(p);
					return pivot;
				}
			}
		}
	}
	free(p);
	return pivot;
}

void init_obstacle(Obstacle* obstacle, int xPos, int yPos, int halfWidth, int halfHeight, int angle, int radius) {
	obstacle->xPos = xPos;
	obstacle->yPos = yPos;
	obstacle->halfWidth = halfWidth;
	obstacle->halfHeight = halfHeight;
	obstacle->angle = angle;
	Point corner;
	//Top Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) - radius - MARGIN;
	corner.y = yPos + (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) + radius + MARGIN;
	obstacle->corners[0] = corner;
	//Top Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) + radius + MARGIN;
	corner.y = yPos + (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) + radius + MARGIN;
	obstacle->corners[1] = corner;
	//Bottom Right Corner
	corner.x = xPos + (halfWidth * dcos(-angle) - halfHeight * dsin(-angle)) + radius + MARGIN;
	corner.y = yPos - (halfHeight * dcos(-angle) + halfWidth * dsin(-angle)) - radius - MARGIN;
	obstacle->corners[2] = corner;
	//Bottom Left Corner
	corner.x = xPos - (halfWidth * dcos(-angle) + halfHeight * dsin(-angle)) - radius - MARGIN;
	corner.y = yPos - (halfHeight * dcos(-angle) - halfWidth * dsin(-angle)) - radius - MARGIN;
	obstacle->corners[3] = corner;
}

void set_obstacle(Node* map[], Obstacle* obstacle, int xMax, int yMax, int radius) {
	//Test uniquement les points qui ont une chance d'etre dans l'obstacle
	int half_diag = sqrt(obstacle->halfWidth * obstacle->halfWidth + obstacle->halfHeight * obstacle->halfHeight) + 2 * (radius + MARGIN);
	for (int i = max(0, obstacle->xPos - half_diag); i < min (xMax, obstacle->xPos + half_diag); i++) {
		for (int j = max(0, obstacle->yPos - half_diag); j < min (yMax, obstacle->yPos + half_diag); j++) {
			if(isInside(map[i * yMax + j]->point, obstacle)) {
				//printf("map[%i][%i] obstacle\n", i, j);
				map[i * yMax + j]->accessible = 0;
			}
		}
	}
}

int isInside(Point point, Obstacle* obstacle) {
	int signe = signof(determinant(point, obstacle->corners[0], obstacle->corners[1]));
	for (int i = 1; i < 4; i++) {
		if(signe != signof(determinant(point, obstacle->corners[i], obstacle->corners[(i + 1) % 4]))) {
			return 0;
		}
	}
	return 1;
}

void printCost(Node* map[], int xMax, int yMax) {
	for (int y = yMax - 1; y >= 0; y--) {
		for (int x = 0; x < xMax; x++) {
			if(map[x * yMax + y]->distance == INT_MAX)
				printf("-1 ");
			else
				printf("%i ", map[x * yMax + y]->distance);
		}
		printf("\n");
	}
}
