using System;
using System.Collections.Generic;
using System.Drawing;

namespace PertNetworkUIExtension
{
	public class PertNetworkItem
	{
		public PertNetworkItem(string title, uint uniqueId)
		{
			Title = title;
			UniqueId = uniqueId;

			Position = new Point(0, 0);
			DependencyUniqueIds = new List<uint>();
		}

		public uint UniqueId
		{
			get;
			private set;
		}

		public string Title;
		public Point Position;
		public List<uint> DependencyUniqueIds;

	}
	// ------------------------------------------------------------

	public class PertNetworkItems : Dictionary<uint, PertNetworkItem>
	{
		public PertNetworkItems()
		{
		}

		void CalcGroupPositions(PertNetworkGroup Group)
		{

			// Calculate horizontal positions first
			foreach (var item in Group.Items)
			{
				item.Position.X = CalcItemHorizontalPosition(item);
			}

			// Calculate vertical positions
		}

		int CalcItemHorizontalPosition(PertNetworkItem item) 
		{
			if (item.DependencyUniqueIds.Count == 0)
				return 0;

			int maxDependLen = 0;

			foreach (var dependId in item.DependencyUniqueIds)
			{
				PertNetworkItem dependItem = null;

				if (TryGetValue(dependId, out dependItem))
				{
					int dependLen = CalcItemHorizontalPosition(dependItem); // RECURSIVE call
					maxDependLen = Math.Max(maxDependLen, dependLen);
				}
			}

			return maxDependLen + 1; // the dependency itself
		}

		List<PertNetworkGroup> BuildGroups(ref int maxVPos)
		{
			var groups = new List<PertNetworkGroup>();

			// Get the set of all tasks on whom other tasks are dependent
			HashSet<uint> dependentIDs = GetAllDependents();

			// Get the set of all tasks which have dependencies but 
			// on whom NO other tasks are dependent
			HashSet<uint> terminatorIDs = GetAllTerminators(dependentIDs);

			// Build the groups by working backwards from each end task
			maxVPos = 0;

			foreach (var termId in terminatorIDs)
			{
				PertNetworkItem termItem = null;

				if (TryGetValue(termId, out termItem))
				{
					if (groups.Count > 0)
						maxVPos += 2;

					var group = new PertNetworkGroup();

					AddTaskToGroup(termItem, group, ref maxVPos);
				}
			}

			return groups;
		}

		HashSet<uint> GetAllDependents()
		{
			var dependentIDs = new HashSet<uint>();
			
			foreach (var item in Values)
			{
				foreach (var depend in item.DependencyUniqueIds)
					dependentIDs.Add(depend);
			}

			return dependentIDs;
		}

		HashSet<uint> GetAllTerminators(HashSet<uint> dependentIDs)
		{
			HashSet<uint> terminatorIds = new HashSet<uint>();

			foreach (var item in Values)
			{
				if ((item.DependencyUniqueIds.Count > 0) && !dependentIDs.Contains(item.UniqueId))
					terminatorIds.Add(item.UniqueId);
			}

			return terminatorIds;
		}

		void AddTaskToGroup(PertNetworkItem item, PertNetworkGroup group, ref int maxVPos)
		{
			if (group.Items.Contains(item))
				return;

			item.Position.X = CalcItemHorizontalPosition(item);
			item.Position.Y = maxVPos;

			group.Items.Add(item);

			// This item's dependencies (can be zero)
			bool firstDepend = true;

			foreach (var dependId in item.DependencyUniqueIds)
			{
				PertNetworkItem dependItem = null;

				if (TryGetValue(dependId, out dependItem))
				{
					if (!firstDepend)
						maxVPos++;
					else
						firstDepend = false;

					AddTaskToGroup(dependItem, group, ref maxVPos); // RECURSIVE call
				}
			}
		}

	}

	// ------------------------------------------------------------

	public class PertNetworkGroup
	{
		public PertNetworkGroup()
		{
			Items = new HashSet<PertNetworkItem>();
			TerminatingItem = null;
		}

		public HashSet<PertNetworkItem> Items;
		public PertNetworkItem TerminatingItem; 
	}

}

