//create graph 
// 1. three poi_n_ts will be given initailly (which will form the plane)
// 2.we will find the normal vector 
// 3.then we will normalize the weight (find the weightd sum)
// 4.find the MST
// 5.again find the vector form of the MST from the normalised one
// 6.since this vector form is the fourth po_in_t 
// now form the 3 plane and then continue the process



#include <bits/stdc++.h>
#include <iostream>
using namespace  std;
vector<vector<double > > gereate_points_of_one_plane(vector<double >p1 , vector<double>p2 , vector<double>p3)
{
    vector<vector<double>>ans;
    ans.push_back(p1);
    ans.push_back(p2);
    ans.push_back(p3);
    return ans;
}
vector<vector<vector<double >>> generate_plane(vector<double>fourth_points , vector<vector<double > >three_point)
{
    vector<vector<vector<double>>>ans;
    //three points of the plane of three different plane 
     vector<vector<double>>temp;
    double size = three_point.size();
    double i , j;
    for(i=0; i<size; i++)
    {
        double cnt = 0;
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
    
    // vector<vector<double>>temp;
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


vector<double> find_fourth_point(vector<vector<double >>MST ,  map<pair<double ,double >  , vector<double > >vector_weight_map)
{
    vector<double> ans;
    // return ans;
    double x = 0 , y = 0 , z =0;
    double n = MST.size();
    pair<double ,double> edge;
    double i;
    for(i=0; i<n; i++)
    {   
        edge.first = MST[i][0];
        edge.second = MST[i][1];
        // auto itr = NULL;
        vector<double>temp;
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

vector<double> find_normal_vector(vector<vector<double >> &three_points)
{
    vector<double > ans;
    double x1,y1,z1,x2,y2,z2,x3,y3,z3;
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
    double a1 = x2 - x1;
    double b1 = y2 - y1;
    double c1 = z2 - z1;
    double a2 = x3 - x1;
    double b2 = y3 - y1;
    double c2 = z3 - z1;
    double a = b1 * c2 - b2 * c1;
    double b = a2 * c1 - a1 * c2;
    double c = a1 * b2 - b1 * a2;
    double length =sqrt(a*a+b*b+c*c);
    double l1=a/length;
    double l2=b/length;
    double l3=c/length;
    //i am scaling the normal vector value (i.e lemda by 10 times)
    if( l1<0 && l2<0 && l3<0 )
    {
        l1 = abs(l1);
        l2 = abs(l2);
        l3 = abs(l3);
    }

    
    if(l1>=0 && l2>=0 && l3>=0)
    {
        ans.push_back(l1);
        ans.push_back(l2);
        ans.push_back(l3);
        cout<<"noraml vector are :- "<<l1<<" "<<l2<<" "<<l3<<endl;
    }
    else{
        cout<<"Normal vector discarded\n";
    }
  
    return ans;
}
//there is no need to pass the MST we need to normalize the weight of the each edge present in the graph
map<pair<double ,double > , double > find_weightedSum(map<pair<double ,double >  , vector<double > >vector_weight_map , vector<double>normal_vector)
{
    //graph and the normal vector will be given 
    // then we will normalize the weight and return it 
    // to keep track of the vector and its corresponding normalized value we will use the map and that will be returned .

    //so i think we can use the map<vector<double >  , double > 
    // map<pair<double , double > , double > will not work i think . 
    
    map<pair<double ,double >  , double> ans;
    double sum;
    double l1,l2,l3;
    l1 = normal_vector[0];
    l2 = normal_vector[1];
    l3 = normal_vector[2];
    double x , y , z , i;
    for(auto itr:vector_weight_map)
    {
        pair<double ,double> edge = itr.first;
        vector<double >temp = itr.second;
        // edge.first = MST[i][0];
        // edge.second = MST[i][1];
        
        // if(vector_weight_map.find({edge.first ,edge.second}) != vector_weight_map.end())
        // {
        //     auto itr1 = vector_weight_map.find({edge.first ,edge.second});
        //     // itr = itr1;
        //     temp = itr1->second;
        // }
        // else{
        //     auto itr2 = vector_weight_map.find({edge.second ,edge.first});
        //     // itr = itr2;
        //     temp = itr2->second;
        // }

        x = temp[0];
        y = temp[1];
        z = temp[2];
        sum = x*l1 + y*l2 + z*l3;
        ans.insert({{edge.first , edge.second} , sum});
        
    }
    return ans;

}

/* finding the minimum spanning tree */

void print_MST(vector<vector<double> > &MST_edge , double cnt)
{
    double n = MST_edge.size();
    double i;
    cout<<"Here is the required  MST ( MST no:- "<<cnt<<")\n";
    cout<<"source node:      destination node:       and their weight:\n";
    for(i=0; i<n; i++)
    {
        cout<<"         "<<MST_edge[i][0]<<"               ";
        cout<<MST_edge[i][1]<<"                      "<<MST_edge[i][2]<<endl;

    }
}

bool static comp(vector<double> v1 , vector<double>v2)
{
    return v1[2] < v2[2];
}

double findParent(double v , vector<double>&parent)
{
    if(parent[v] == v)
    {
        return v;
    }
    return findParent(parent[v] , parent);
}
vector<vector<double >> find_MST(vector<vector<double > >&graph , map<pair<double ,double > , double > weightSum )
{
    vector<vector<double >> ans;
    vector<vector<double>>edges;
    double no_of_edges = weightSum.size();
    double no_of_vertices = graph.size();
    pair<double, double > temp_edge;
    double temp_weight;

    vector<double>parent(no_of_vertices , 0);
    
    for(auto itr:weightSum)
    {
        temp_edge = itr.first;
        temp_weight = itr.second;
        vector<double>v;
        v.push_back(temp_edge.first);
        v.push_back(temp_edge.second);
        v.push_back(temp_weight);
        edges.push_back(v);
    }

    sort(edges.begin(), edges.end() , comp);//we have sorted the array according to the weight of the edges .

    double i = 0;
    for(i=0; i<no_of_vertices; i++)
    {
        parent[i] = i;
    }
    double cnt = 0;
    i = 0;
    while(cnt != no_of_vertices - 1)
    {
        vector<double> v = edges[i];
        //now we have to check whether we can include this edges doubleo the MST or not .
        //for that we have to check for  , if it is making cycle or not if it is not making the cycle then we will
        // include this doubleo the MST . we will use disjodouble set union to check for the cycle in the graph .

        double srcparent  = findParent(v[0] , parent);
        double desparent  = findParent(v[1] , parent);

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

void print_weight( map<pair<double ,double >  , vector<double > >vector_weight_map)
{
    pair<double ,double >temp;
    vector<double> v;
    for(auto itr:vector_weight_map)
    {
        temp = itr.first;
        v = itr.second;
        cout<<"weight for the edge connected by the vectices "<<temp.first<<" and "<<temp.second<<endl;
        for(double i = 0; i<v.size(); i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
}

void print_graph(vector<vector<double> >&graph)
{
    double n = graph.size();
    double i , j;
    for(i=0; i<n; i++)
    {
        double node = i;
        cout<<"node connected with "<<node<<" are:-"<<endl;
        for(j=0; j<graph[node].size(); j++)
        {
            cout<<graph[node][j]<<" ";
        }
        cout<<endl;
    }

}
vector<vector<double> > creat_graph(map< pair<double ,double > , vector<double > >&vector_weight_map)
{
    //create the graph 
    //we need to take the weight also in the vector ans i have to make this weight to the corresponding edges.
    //lets taka the input of the weight as well .
    double n , e , no_of_attributes_of_weight;
    cout<<"Enter the number of vertices and edges as well as number of attributes of weight \n";
    cin>>n>>e>>no_of_attributes_of_weight;
    vector<vector<double>> graph(n);
    vector<double>weight(no_of_attributes_of_weight , 0);
    double node1 , node2;
    double i , j;
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
void print_extremal_point(vector<vector<double>>&extremal_point)
{
    double n = extremal_point.size();
    double i;
    
    // double cnt = 0;
    // cout<<"we are getting "<<n<<" extremal points\n";
    cout<<"Extremal points are :- \n";
    if(n == 0){
        cout<<"unfortunately no extremal points found\n";
        return ;
    }
    for(i=0; i<n; i++)
    {
        for(double j=0; j<extremal_point[i].size(); j++)
        {
            cout<<extremal_point[i][j]<<" ";
        }
        cout<<endl;
    }
}
vector<vector<double>> BFS(vector<vector<double >> initial_three_point , vector<vector<double >>&graph,  map<pair<double ,double >  , vector<double > >vector_weight_map)
{

    //it will return the set of the extreaml points 

    //we wiil use the queue data structure for solving EST like we so BFS 
    //que.push({plane which are at infinite disatance })--> starting 
    

    //we also use chechker to keep track of the farthest we have calculated till now to avoid the 
    // repeatation and it will also increase the efficency of the code.

    vector<vector<double > > ans;
    queue<vector<vector<double >>> que;
    que.push(initial_three_point);
    double cnt = 0;
    while(!que.empty())
    {
        double size = que.size();
        while(size--)
        {
            vector<vector<double>>temp_three_point = que.front();
            que.pop();
            // first i have to calculate the fourth point by using the three_point 

            // vector<double> find_normal_vector(vector<vector<double >> &three_points)
            //find the normal vector then--
            vector<double>normal_vector = find_normal_vector(temp_three_point);

            // map<pair<double ,double > , double > find_weightedSum(vector<vector<double >>MST,  map<pair<double ,double >  , vector<double > >vector_weight_map , vector<double>normal_vector)
            // then find the normalized weight then -- 
            map<pair<double ,double > , double > normlized_weight;
            if(!normal_vector.size())
            {
                continue; 
            }
            normlized_weight = find_weightedSum(vector_weight_map , normal_vector);


            // vector<vector<double >> find_MST(vector<vector<double > >&graph , map<pair<double ,double > , double > weightSum )
            // then find the MST

            vector<vector<double>> set_of_edges_of_MST;
            set_of_edges_of_MST = find_MST(graph , normlized_weight);
            cnt++;
            print_MST(set_of_edges_of_MST , cnt);
            

            // vector<double> find_fourth_point(vector<vector<double >>MST ,  map<pair<double ,double >  , vector<double > >vector_weight_map)
            //then find the fourth point --(done)
            vector<double>fourth_point = find_fourth_point(set_of_edges_of_MST , vector_weight_map);

            // vector<vector<vector<double >>> generate_plane(vector<double>fourth_points , vector<vector<double > >three_point)
            // generate_plane(fourth_point , three_point)
            vector<vector<vector<double>>>three_plane = generate_plane(fourth_point , temp_three_point);

            if(three_plane.size() == 1)
            {
                ans.push_back(three_plane[0][0]);
            }
            else{
                for(double i = 0; i<three_plane.size(); i++)
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
    double dimension;
    cout<<"Enter the dimension of weight of the graph (number of attributes\n";
    cin>>dimension;
    double i;
    vector<double>temp;

    vector<vector<double>>initial_point;//we will take the inital point as an input and we will pass this initial point in
    // the BFS()  fucntion 

    cout<<"now enter the initial ponts\n";
    for(i=0; i<dimension; i++)
    {
        temp.clear();
        for(double j = 0; j<dimension; j++)
        {
            double val;
            cin>>val;
            temp.push_back(val);
        }
        initial_point.push_back(temp);
    }
    vector<vector<double>>graph;//in this graph variable i will store the graph returned by the creat_graph function .

    map<pair<double ,double >  , vector<double > >vector_weight_map;//we will this as a reference the after graph will be created 
    // we will get the weight will mapped which are in the vector form .

    graph = creat_graph(vector_weight_map); //we will be creating the graph;

    print_graph(graph);

    print_weight(vector_weight_map);

    vector<vector<double>> exrtimal_points;

    exrtimal_points = BFS( initial_point,graph, vector_weight_map);
    print_extremal_point(exrtimal_points);

    return 0;
}
//graph input 1
// 6 6 3
// 0 4 1 3 19
// 0 1 12 12 1
// 0 2 178 1 43
// 2 3 1 1 23
// 2 5 132 15 90
// 5 3 1 18 1000

// graph input 2
// 7 9 3
// 0 1 1 2 1
// 0 4 3 4 6
// 0 2 8 9 4
// 0 3 9 343 3
// 4 2 5 4 3
// 4 6 234 1 8
// 2 5 876 9 12
// 2 3 26 4 6
// 6 5 234 5 789

// initail three points 
// 1000 0 0
// 0 10000 0
// 0 0 1000

// initail three points 
// 234 23 656
// 56 567 234
// 23 789 100 




   // cout<<"value of lamda 1 is: "<<l1<<"\nvalue of lamda 2 is: "<<l2<<"\nvalue of lamda 3 is: "<<l3;
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
    then values of lamda are 
    value of lamda 1 is: 0.316228
    value of lamda 2 is: -0.948683
    value of lamda 3 is: 0 */


    // to test the find_MST() function i am making the map(weightSum) 
    // map<pair<double ,double > ,  double  > map1;
    // double n , e;
    // cout<<"Enter the number of edges \n";
    // cin>>e;
    // double i;
    // pair<double , double > edge;
    // double weight;
    // for(i=0; i<e; i++)
    // {
    //     cin>>edge.first>>edge.second>>weight;
    //     map1.insert({edge , weight});
    // }



    // map<pair<double , double  > , double > scaler_weight_map;

    // vector<vector<double>> MST_edge;

    // MST_edge =  find_MST(graph , scaler_weight_map);

    // print_MST(MST_edge);




    // find_MST();//it will calculate all the possible ST (probably it should be given in the questoin)
    // solve_EST();
