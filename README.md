# Endeavor Engine

<p> Endeavor is an open source game engine I'm working on in my spare time. Endeavor is designed to be easy to use, and the codebase is designed to be easily understood. Its primary purpose is to expand my abilities as a programmer, but I hope to see it grow to become a viable tool in the development of 2D games. </p>

<h2> Performant </h2>
<p> Endeavor's runtime environment is built on ECS (Entity-Component-System) architecture, implemented through the popular <a href="https://github.com/skypjack/entt"> EnTT </a> framework. You can read about the benefits of ECS over other approaches <a href="https://digitalcommons.calpoly.edu/cgi/viewcontent.cgi?article=1138&context=cpesp"> here.</a> In short, ECS provides a more modular approach to game logic and avoids common performance issues found in a more traditional object-oriented design.


In Endeavor, Entities can be created in a Scene, and Components can be attached to those Entities. Endeavor references the Components and simulates their behavior with Systems. In this way, users can take advantage of complex behaviors such as collision or rendering simply by adding the necessary components to their Entities.


<h2> Extensible </h2>
Endeavor allows for custom behavior implemented through a native Scripting API. Users can use the Script Component along with extending Endeavor's own Behavior class to script their own logic into Entities. Endeavor's API allows Entities to respond to player input and other events programmatically.

<h2> User-Oriented </h2>
By providing an ECS runtime combined with a native scripting API, Endeavor strives to provide the best of both worlds:


- Where performance is critical, Endeavor will employ a powerful data-oriented paradigm to accomplish computationally heavy tasks that need to be performed each frame. This includes core engine behaviors such as physics integrations and rendering.


- When it's time to implement custom logic, Endeavor's native scripting API allows for responsive behavior to events such as user input, menu interactions, and callbacks for collision events. Scripts allow users to work in a more familiar object-oriented way and avoid the complexities of ECS where it's not needed.
