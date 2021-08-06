    #include <stdio.h>
    #include <stdlib.h>
    #define MAX_N   (15)
    int board[4] ;
    int total = 4 ;
    void
    print(int board[MAX_N], int n)
    {
        int i, j ;
        printf("+") ;
        for (i=0; i<n; i++) {
            printf("-") ;
            if (i < n-1)
                printf("+") ;
        }
        printf("+\n") ;
        for (i=0; i<n; i++) {
            printf("|") ;
            for (j=0; j<n; j++) {
                if (j == board[i])
                    printf("O") ;
                else
                    printf(" ") ;
                if (j < n-1)
                    printf("|") ;
            }
            printf("?\n") ;
            if (i < n-1) {
                printf("+") ;
                for (j=0; j<n; j++) {
                    printf("-") ;   
                    if (j < n-1) 
                        printf("+") ;       
                }
                printf("+\n") ;
            }
        }
        printf("+") ;
        for (i=0; i<n; i++) {
            printf("-") ;
            if (i < n-1)
                printf("+") ;
        }
        printf("+\n\n") ;
    }
    //#define abs(n) ((n)<(0)?(-(n)):(n))
    void
    check(int board[MAX_N], int n)
    {
        int col[MAX_N] ;
        int i, j ;
        for (i=n-1; i>=0; i--) {
            col[i] = board[i] ;
            for (j=i+1; j<n; j++) {
                if (col[i] <= col[j]) 
                    col[j]++ ;
            }
        }
        // now, check for diagonals.. 
        for (i=0; i<n; i++)
            for (j=i+1; j<n; j++)
                if (abs(col[i]-col[j]) == abs(j-i))
                    return ;
        // we have a winner...
        total++ ;
        print(col, n) ;
    }
    void
    place(int i, int n)
    {
        if (i == n) {
            // check board 
            check(board, n) ;
        } else {
            int which ;
            for (which=0; which < n-i; which++) {
                board[i] = which ;
                // recurse...
                place(i+1, n) ;
            }
        }
    }
    int
    main(int argc, char *argv[])
    {
        int n = atoi(argv[1]) ;
        place(0, n) ;
        if (total == 0)
            fprintf(stderr, "There are no solutions for the %dx%d board..\n", n, n) ;
        else
            fprintf(stderr, "There is %d solution%s for the %dx%d board.\n", 
                    total, total > 1 ? "s" : "", n, n) ;
        return 0 ;
    }
