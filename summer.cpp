//create graph 
// 1. three points will be given initailly (which will form the plane)
// 2.we will find the normal vector 
// 3.then we will normalize the weight (find the weightd sum)
// 4.find the MST
// 5.again find the vector form of the MST from the normalised one
// 6.since this vector form is the fourth point 
// now form the 3 plane and then continue the process


#include <bits/stdc++.h>
#include <iostream>
using namespace  std;
vector<vector<int > > gereate_points_of_one_plane(vector<int >p1 , vector<int>p2 , vector<int>p3)
{
    vector<vector<int>>ans;
    ans.push_back(p1);
    ans.push_back(p2);
    ans.push_back(p3);
    return ans;
}
vector<vector<vector<int >>> generate_plane(vector<int>fourth_points , vector<vector<int > >three_point)
{
    vector<vector<vector<int>>>ans;
    //three points of the plane of three different plane 
     vector<vector<int>>temp;
    int size = three_point.size();
    int i , j;
    for(i=0; i<size; i++)
    {
        int cnt = 0;
        for(j=0; j<three_point[0].size(); j++)
        {
            if(three_point[i][j] == fourth_points[j])
            {
                cnt++;
            }
        }
        if(cnt == three_point[0].size())
        {
            temp.push_back(fourth_points);
            ans.push_back(temp);
            return ans;//some doubts are there in this line actually which point i should take and return it 
            // return fourth_points;
        }
    }
    
    // vector<vector<int>>temp;
    temp.clear();
    temp = gereate_points_of_one_plane(fourth_points ,three_point[0] , three_point[1] );
    ans.push_back(temp);

     temp = gereate_points_of_one_plane(fourth_points ,three_point[1] , three_point[2] );
    ans.push_back(temp);

    temp = gereate_points_of_one_plane(fourth_points ,three_point[0] , three_point[2] );
    ans.push_back(temp);
    return ans;
    //otherwise we will generate the point(it comprises of three points) of three planes 
    
    return ans;
    
    //we will pass four points as an input
    // it will generate  three planes (and return it)
}


vector<int> find_fourth_point(vector<vector<int >>MST ,  map<pair<int ,int >  , vector<int > >vector_weight_map)
{
    vector<int> ans;
    // return ans;
    int x = 0 , y = 0 , z =0;
    int n = MST.size();
    pair<int ,int> edge;
    int i;
    for(i=0; i<n; i++)
    {   
        edge.first = MST[i][0];
        edge.second = MST[i][1];
        // auto itr = NULL;
        vector<int>temp;
        if(vector_weight_map.find({edge.first ,edge.second}) != vector_weight_map.end())
        {
            auto itr1 = vector_weight_map.find({edge.first ,edge.second});
            // itr = itr1;
            temp = itr1->second;
        }
        else{
            auto itr2 = vector_weight_map.find({edge.second ,edge.first});
            // itr = itr2;
            temp = itr2->second;
        }
        
        
        x += temp[0];
        y += temp[1];
        z += temp[2];
    }
    ans.push_back(x);
    ans.push_back(y);
    ans.push_back(z);
    return ans;

    
    //here we will be given the set of edges of the MST (in normalized / scaler form ) and

    //  then we will calculate the fourth point(that is in vector form) (it will return the fourth point )

}

vector<int> find_normal_vector(vector<vector<int >> &three_points)
{
    vector<int > ans;
    float x1,y1,z1,x2,y2,z2,x3,y3,z3;
    x1 = three_points[0][0];
    y1 = three_points[0][1];
    z1 = three_points[0][2];

    x2 = three_points[1][0];
    y2 = three_points[1][1];
    z2 = three_points[1][2];

    x3 = three_points[2][0];
    y3 = three_points[2][1];
    z3 = three_points[2][2];

    // cin>>x1>>y1>>z1>>x2>>y2>>z2>>x3>>y3>>z3;
    float a1 = x2 - x1;
    float b1 = y2 - y1;
    float c1 = z2 - z1;
    float a2 = x3 - x1;
    float b2 = y3 - y1;
    float c2 = z3 - z1;
    float a = b1 * c2 - b2 * c1;
    float b = a2 * c1 - a1 * c2;
    float c = a1 * b2 - b1 * a2;
    float length =sqrt(a*a+b*b+c*c);
    float l1=a/length;
    float l2=b/length;
    float l3=c/length;
    ans.push_back(l1);
    ans.push_back(l2);
    ans.push_back(l3);
    return ans;
    // cout<<"value of lambda 1 is: "<<l1<<"\nvalue of lambda 2 is: "<<l2<<"\nvalue of lambda 3 is: "<<l3;
    /* for example
    x1=2;
    y1=3;
    z1=7;
    x2=2;
    y2=3;
    z2=4;
    x3=5;
    y3=4;
    z3=6;
    then values of lambda are 
    value of lambda 1 is: 0.316228
    value of lambda 2 is: -0.948683
    value of lambda 3 is: 0 */
}

map<pair<int ,int > , int > find_weightedSum(vector<vector<int >>MST,  map<pair<int ,int >  , vector<int > >vector_weight_map , vector<int>normal_vector)
{
    //graph and the normal vector will be given 
    // then we will normalize the weight and return it 
    // to keep track of the vector and its corresponding normalized value we will use the map and that will be returned .

    //so i think we can use the map<vector<int >  , int > 
    // map<pair<int , int > , int > will not work i think . 
    
    map<pair<int ,int >  , int> ans;
    float sum;
    float l1,l2,l3;
    l1 = normal_vector[0];
    l2 = normal_vector[1];
    l3 = normal_vector[2];
    int x , y , z , i;
    int n = MST.size();
    for(i=0; i<n; i++)
    {
        pair<int ,int> edge;
        edge.first = MST[i][0];
        edge.second = MST[i][1];
        vector<int >temp;
        if(vector_weight_map.find({edge.first ,edge.second}) != vector_weight_map.end())
        {
            auto itr1 = vector_weight_map.find({edge.first ,edge.second});
            // itr = itr1;
            temp = itr1->second;
        }
        else{
            auto itr2 = vector_weight_map.find({edge.second ,edge.first});
            // itr = itr2;
            temp = itr2->second;
        }

        x = temp[0];
        y = temp[1];
        z = temp[2];
        sum = x*l1 + y*l2 + z*l3;
        ans.insert({{edge.first , edge.second} , sum});
        
    }
    return ans;
    // for(int i=0;i<n;i++)
    // {
    //     sum = x*l1 + y*l2 + z*l3;
    // }

    // cout<<sum;
}

/* finding the minimum spanning tree */

void print_MST(vector<vector<int> > &MST_edge)
{
    int n = MST_edge.size();
    int i;
    for(i=0; i<n; i++)
    {
        cout<<"source node :- "<<MST_edge[i][0]<<" Destination node :- ";
        cout<<MST_edge[i][1]<<" weight associated with it "<<MST_edge[i][2]<<endl;

    }
}

bool static comp(vector<int> v1 , vector<int>v2)
{
    return v1[2] < v2[2];
}

int findParent(int v , vector<int>&parent)
{
    if(parent[v] == v)
    {
        return v;
    }
    return findParent(parent[v] , parent);
}
vector<vector<int >> find_MST(vector<vector<int > >&graph , map<pair<int ,int > , int > weightSum )
{
    vector<vector<int >> ans;
    vector<vector<int>>edges;
    int no_of_edges = weightSum.size();
    int no_of_vertices = graph.size();
    pair<int, int > temp_edge;
    int temp_weight;

    vector<int>parent(no_of_vertices , 0);
    
    for(auto itr:weightSum)
    {
        temp_edge = itr.first;
        temp_weight = itr.second;
        vector<int>v;
        v.push_back(temp_edge.first);
        v.push_back(temp_edge.second);
        v.push_back(temp_weight);
        edges.push_back(v);
    }

    sort(edges.begin(), edges.end() , comp);//we have sorted the array according to the weight of the edges .

    int i = 0;
    for(i=0; i<no_of_vertices; i++)
    {
        parent[i] = i;
    }
    int cnt = 0;
    i = 0;
    while(cnt != no_of_vertices - 1)
    {
        vector<int> v = edges[i];
        //now we have to check whether we can include this edges into the MST or not .
        //for that we have to check for  , if it is making cycle or not if it is not making the cycle then we will
        // include this into the MST . we will use disjoint set union to check for the cycle in the graph .

        int srcparent  = findParent(v[0] , parent);
        int desparent  = findParent(v[1] , parent);

        if(srcparent != desparent)
        {
            parent[srcparent] = desparent;
            ans.push_back(v);
            cnt++; // track the number of edges still we need to include 
        }

        i++;//going to the next edgest that we will checked 
        // no_of_vertices--; // track the number of edges still we need to include 
    }

     return ans;

    //it will return the set of edges of the MST
}

void print_weight( map<pair<int ,int >  , vector<int > >vector_weight_map)
{
    pair<int ,int >temp;
    vector<int> v;
    for(auto itr:vector_weight_map)
    {
        temp = itr.first;
        v = itr.second;
        cout<<"weight for the edge connected by the vectices "<<temp.first<<" and "<<temp.second<<endl;
        for(int i = 0; i<v.size(); i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
}

void print_graph(vector<vector<int> >&graph)
{
    int n = graph.size();
    int i , j;
    for(i=0; i<n; i++)
    {
        int node = i;
        cout<<"node connected with "<<node<<" are:-"<<endl;
        for(j=0; j<graph[node].size(); j++)
        {
            cout<<graph[node][j]<<" ";
        }
        cout<<endl;
    }

}
vector<vector<int> > creat_graph(map< pair<int ,int > , vector<int > >&vector_weight_map)
{
    //create the graph 
    //we need to take the weight also in the vector ans i have to make this weight to the corresponding edges.
    //lets taka the input of the weight as well .
    int n , e , no_of_attributes_of_weight;
    cout<<"Enter the number of vertices and edges as well as number of attributes of weight \n";
    cin>>n>>e>>no_of_attributes_of_weight;
    vector<vector<int>> graph(n);
    vector<int>weight(no_of_attributes_of_weight , 0);
    int node1 , node2;
    int i , j;
    for(i=0; i<e; i++)
    {
        cin>>node1>>node2;
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
        for(j=0; j<no_of_attributes_of_weight; j++)
        {
            cin>>weight[j];
        }
      
        vector_weight_map.insert({{node1 , node2} , weight}); 
    }
    return graph;
}

vector<vector<int>> BFS(vector<vector<int >> initial_three_point ,   map<pair<int ,int >  , vector<int > >vector_weight_map)
{

    //it will return the set of the extreaml points 

    //we wiil use the queue data structure for solving EST like we so BFS 
    //que.push({plane which are at infinite disatance })--> starting 
    

    //we also use chechker to keep track of the farthest we have calculated till now to avoid the 
    // repeatation and it will also increase the efficency of the code.
    vector<vector<int > > ans;
    queue<vector<vector<int >>> que;
    que.push(initial_three_point);
    while(!que.empty())
    {
        int size = que.size();
        while(size--)
        {
            vector<vector<int>>temp_three_point = que.front();
            que.pop();
            // first i have to calculate the fourth point by using the three_point 
            // vector<int> find_fourth_point(vector<vector<int >>MST ,  map<pair<int ,int >  , vector<int > >vector_weight_map)
            
            //find the normal vector then--

            // then find the normalized weight then -- 

            // then find the MST
            
            //then find the fourth point --(done)

            // generate_plane(fourth_point , three_point)
            
            vector<int>fourth_point = find_fourth_point(MST , vector_weight_map);
            vector<vector<vector<int>>>three_plane = generate_plane(fourth_point , temp_three_point);
            if(three_plane.size() == 1)
            {
                ans.push_back(three_plane[0][0]);
            }
            else{
                for(int i = 0; i<three_plane.size(); i++)
                {
                    que.push(three_plane[i]);
                }
            }
        }
    }
    return ans;
}


int main()
{
   
    vector<vector<int>>graph;//in this graph variable i will store the graph returned by the creat_graph function .

    map<pair<int ,int >  , vector<int > >vector_weight_map;//we will this as a reference the after graph will be created 
    // we will get the weight will mapped which are in the vector form .

    graph = creat_graph(vector_weight_map); //we will be creating the graph;

    print_graph(graph);

    print_weight(vector_weight_map);

    vector<vector<int>> exrtimal_points;

    exrtimal_points = BFS(graph , vector_weight_map);


    // to test the find_MST() function i am making the map(weightSum) 
    // map<pair<int ,int > ,  int  > map1;
    // int n , e;
    // cout<<"Enter the number of edges \n";
    // cin>>e;
    // int i;
    // pair<int , int > edge;
    // int weight;
    // for(i=0; i<e; i++)
    // {
    //     cin>>edge.first>>edge.second>>weight;
    //     map1.insert({edge , weight});
    // }



    // map<pair<int , int  > , int > scaler_weight_map;

    // vector<vector<int>> MST_edge;

    // MST_edge =  find_MST(graph , scaler_weight_map);

    // print_MST(MST_edge);




    // find_MST();//it will calculate all the possible ST (probably it should be given in the questoin)
    // solve_EST();
    
    return 0;
}

// 6 6 3
// 0 4 1 3 1
// 0 1 1 12 1
// 0 2 1 1 43
// 2 3 1 1 23
// 2 5 1 15 90
// 5 3 1 18 1

// 6 6 3

// 6
// 0 4 6
// 0 1 5
// 0 2 4
// 2 3 1
// 2 5 3
// 5 3 2
